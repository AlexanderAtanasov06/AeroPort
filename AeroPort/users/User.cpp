#include "User.h"

User::User(const std::string& name, const std::string& pass, Role role) : name(name), pass(pass), role(role) {}

void User::logout() {
	std::println("[System] Logged out successfully.");
}

std::string User::getName() const {
	return name;
}

bool User::checkPassword(const std::string& pass) const {
	return this->pass == pass;
}

User::Role User::getRole() const {
	return role;
}

std::string User::getRoleStr() const {
	if (role == User::Role::AIRPORT_AUTHORITY) {
		return "System Administrator";
	}
	else if (role == User::Role::AIR_TRAFFIC_CONTROL) {
		return "Dispatcher";
	}
	else if (role == User::Role::PASSENGER) {
		return "Passenger";
	}
}

