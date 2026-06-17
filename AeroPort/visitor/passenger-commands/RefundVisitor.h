#pragma once
#include "UserVisitor.h"
#include "Ticket.h"
#include "Flight.h"
#include "Passenger.h"
#include <print>
#include <string>

class RefundTicketVisitor : public UserVisitor {
	std::string passengerName;
	std::string flightID;
public:
	RefundTicketVisitor(const std::string& passengerName, const std::string& flightID);

	void visit(Passenger& p) override;
	void visit(AirportAuthority& a) override;
	void visit(Dispatcher& a) override;
};