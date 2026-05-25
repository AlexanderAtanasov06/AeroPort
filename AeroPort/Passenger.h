#pragma once
#include "User.h"
#include "Ticket.h"

class Passenger : public User {
private:
	double funds;
public:
	Passenger(const std::string& name, const std::string& pass);

	void addFunds(double amount);
	void bookTicket(const std::string& flightID, Ticket::TicketType ticketType);
	void upgradeTicket(const std::string& flightID, Ticket::TicketType newType);
	void addBaggage(const std::string& flightID, double weight);
	void cancelTicket(const std::string& flightID);

	void listFlights(const std::string& destination) const;
	void filterFlights(double maxPrice) const;
	void listTickets() const;
};