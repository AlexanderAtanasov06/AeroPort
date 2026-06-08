#pragma once
#include "Ticket.h"

class VIPTicket : public Ticket {
public:
	VIPTicket(const std::string& passengerName, const std::string& flightID, double baseFlightPrice);
	double getRefundAmount() override;
	bool isRefundable() override;
};
