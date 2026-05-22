#pragma once
#include "Ticket.h"

class StandardTicket : public Ticket{
	double getRefundAmount() override;
	bool isRefundable() override;
};

