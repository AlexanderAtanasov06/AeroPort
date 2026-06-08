#pragma once
#include "Ticket.h"

class StandardTicket : public Ticket {
public:
	StandardTicket(const std::string& passengerName, const std::string& flightID, double baseFlightPrice);
	double getRefundAmount() override;
	bool isRefundable() override;
};

