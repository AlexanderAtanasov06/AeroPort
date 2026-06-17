#include "AirportAuthority.h"

AirportAuthority::AirportAuthority() 
	: User("admin", "admin", Role::AIRPORT_AUTHORITY) {
}

AirportAuthority& AirportAuthority::getInstance() {
	static AirportAuthority instance;
	return instance;
}

void AirportAuthority::help() const {
	std::println("[System] Available commands for Administrator: build-runway, build-hangar, close-runway, set-weather, register-airline, buy-aircraft, clone-aircraft, send-to-hangar, schedule-flight, retrieve-from-hangar, cancel-flight, flight-revenue, list-fleet, airport-report, audit-airline, view-profile, logout, save, load");
}

void AirportAuthority::accept(CommandVisitor& visitor) {
	visitor.visit(*this);
}

void AirportAuthority::accept(UserVisitor& visitor) {
	visitor.visit(*this);
}

void AirportAuthority::viewProfile() const {
	std::println("[Profile] User: {} | Role: System Administrator | Privilege: ALL_ACCESS", name);
}

