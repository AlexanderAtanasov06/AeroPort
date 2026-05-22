#pragma once
#include "Ticket.h"

class VIPTicket : public Ticket {
	double getRefundAmount() override;
	bool isRefundable() override;
};
