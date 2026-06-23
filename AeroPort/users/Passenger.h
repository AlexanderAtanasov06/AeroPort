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

	bool addFunds(double amount);
	void deductFunds(double amount);

	void addTicket(std::shared_ptr<Ticket> ticket);
	void removeTicket(const std::shared_ptr<Ticket>& ticket);
	void removeTicketsWithFlightID(const std::string& flightID);

	const std::vector<std::shared_ptr<Ticket>>& getTickets() const;
	double getBalance() const;

	void accept(CommandVisitor& visitor) override;
	void accept(UserVisitor& userVisitor) override;

};