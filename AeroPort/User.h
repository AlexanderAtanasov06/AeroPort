#pragma once
#include <iostream>

class User {
protected:
	std::string name;
	std::string pass;
	enum class Role {
		PASSENGER,
		AIR_TRAFFIC_CONTROL,
		AIRPORT_AUTHORITY
	};
public:
	virtual void logout() = 0;
	virtual void help() = 0;
	virtual void viewProfile() = 0;
};