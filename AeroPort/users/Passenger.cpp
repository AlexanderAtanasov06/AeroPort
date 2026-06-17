#include "Passenger.h"

Passenger::Passenger(const std::string& name, const std::string& pass, double initialFunds)
	: User(name, pass, Role::PASSENGER), balance(initialFunds) {
}

void Passenger::help() const {
	std::println(
		R"([System] Available commands for Passenger:
add-funds - "add-funds <amount>"
list-flights - "list-flights <destination>"
filter-flights - "filter-flights <max price>"
book-ticket - "book-ticket <flight ID> <ticket type>"
upgrade-ticket - "upgrade-ticket <flight ID> <new ticket type>"
add-baggage - "add-baggage <flight ID> <weight>"
cancel-ticket - "cancel-ticket <flight ID>"
my-tickets - "lists all tickets and their flight status"
view-profile - "shows information about your profile"
logout - "logs you out of the system")"
);
}

bool Passenger::addFunds(double amount) {
	balance += amount;
	return true;
}

void Passenger::deductFunds(double amount) {
	balance -= amount;
}

void Passenger::addTicket(std::shared_ptr<Ticket> ticket) {
	tickets.push_back(ticket);
}

void Passenger::removeTicketsWithFlightID(const std::string& flightID) {
	std::erase_if(tickets, [&flightID](const auto& ticket) {
		return flightID == ticket->getFlightID();
		});
}

const std::vector<std::shared_ptr<Ticket>>& Passenger::getTickets() const {
	return tickets;
}

double Passenger::getBalance() const {
	return balance;
}

void Passenger::accept(CommandVisitor& visitor) {
	visitor.visit(*this);
}

void Passenger::accept(UserVisitor& userVisitor) {
	userVisitor.visit(*this);
}

void Passenger::viewProfile() const {
	std::println("[Profile] User: {} | Role: {} | Balance: {:.2f} EUR", name, getRoleStr(), balance);
}
