#include "Passenger.h"

Passenger::Passenger(const std::string& name, const std::string& pass, double initialFunds)
	: User(name, pass, Role::PASSENGER), funds(initialFunds) {
}

void Passenger::help() const {
	std::println(
		R"([System] Available commands for Passenger:
add-funds - "command description"
list-flights - "command description"
filter-flights - "command description"
book-ticket - "command description"
upgrade-ticket - "command description"
add-baggage - "command description"
cancel-ticket - "command description"
my-tickets - "command description"
view-profile - "command description"
logout - "command description")"
);
}

void Passenger::addFunds(double amount) {
	funds += amount;
}

void Passenger::bookTicket(const std::string& flightID, std::string& ticketType) {
	//auto ticket = TicketFactory::createTicket(ticketType, name, flightID, )
}

void Passenger::accept(CommandVisitor& visitor) {
	visitor.visit(*this);
}
