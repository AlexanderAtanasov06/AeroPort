#pragma once
#include "User.h"
#include "Ticket.h"
#include "TicketFactory.h"
#include <vector>

class Passenger : public User {
private:
	double balance;
	std::vector<std::shared_ptr<Ticket>> tickets;
public:
	Passenger(const std::string& name, const std::string& pass, double initialFunds = 0);

	void help() const override;
	void viewProfile() const override;

	void addFunds(double amount);
	void bookTicket(const std::string& flightID, std::string& ticketType);
	void upgradeTicket(const std::string& flightID, std::string& newTicketType);
	void addBaggage(const std::string& flightID, double weight);
	void cancelTicket(const std::string& flightID);

	void listFlights(const std::string& destination) const;
	void filterFlights(double maxPrice) const;
	void listTickets() const;

	double getBalance() const;

	void accept(CommandVisitor& visitor) override;

};