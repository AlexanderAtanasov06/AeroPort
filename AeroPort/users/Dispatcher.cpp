#include "Dispatcher.h"

Dispatcher::Dispatcher(const std::string& name, const std::string& pass)
	: User(name, pass, User::Role::AIR_TRAFFIC_CONTROL) {
}

void Dispatcher::help() const {
	std::println(
		"[System] Available commands for Dispatcher: list-airspace, list-runways, assign-runway, delay-flight, free - runway, undo, view - profile, logout"
	);
}

void Dispatcher::accept(CommandVisitor& visitor) {
	visitor.visit(*this);
}

void Dispatcher::accept(UserVisitor& visitor) {
	visitor.visit(*this);
}

void Dispatcher::viewProfile() const {
	std::println("[Profile] User: {} | Role: Air Traffic Control", name);
}
