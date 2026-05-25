#include "Passenger.h"

Passenger::Passenger(const std::string& name, const std::string& pass, double initialFunds)
	: User(name, pass, Role::PASSENGER), funds(initialFunds) {
}

void Passenger::addFunds(double amount) {
	funds += amount;
}

void Passenger::bookTicket(const std::string& flightID, std::string& ticketType) {
	//auto ticket = TicketFactory::createTicket(ticketType, name, flightID, )
}
