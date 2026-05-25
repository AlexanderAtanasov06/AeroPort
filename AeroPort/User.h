#pragma once
#include <string>

class User {
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

	/*virtual void logout() = 0;
	virtual void help() const = 0;
	virtual void viewProfile() const = 0;*/

	std::string getName() const;
	bool checkPassword(const std::string& pass) const;
	Role getRole() const;
};