#pragma once
#include "Ticket.h"

class LastMinuteTicket : public Ticket{
public:
	LastMinuteTicket(const std::string& passengerName, const std::string& flightID, double baseFlightPrice);
	double getRefundAmount() override;
	bool isRefundable() override;
};