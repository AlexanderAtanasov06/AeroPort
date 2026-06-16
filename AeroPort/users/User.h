#pragma once
#include <string>
#include <print>
#include "IUserActions.h"
#include "CommandVisitor.h"

class Engine;

class User : public IUserActions {
public:
	enum class Role {
		PASSENGER,
		AIR_TRAFFIC_CONTROL,
		AIRPORT_AUTHORITY
	};
protected:
	std::string name;
	std::string pass;
	Role role;
public:
	User(const std::string& name, const std::string& pass, Role role);
	virtual ~User() = default;

	//virtual void handleCommand(std::vector<std::string>& args, Engine& engine) = 0;

	virtual void logout();
	virtual void help() const = 0;
	virtual void viewProfile() const = 0;

	virtual void accept(CommandVisitor& visitor) = 0;

	std::string getName() const;
	bool checkPassword(const std::string& pass) const;
	Role getRole() const;
	std::string getRoleStr() const;
};