#pragma once
#include "Ticket.h"

class LastMinuteTicket : public Ticket{
public:
	LastMinuteTicket(const std::string& name, const std::string& flightID, double amount, double baggage);
	double getRefundAmount() override;
	bool isRefundable() override;
};