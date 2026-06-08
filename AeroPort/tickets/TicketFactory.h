#pragma once
#include <memory>
#include "Ticket.h"
#include "StandardTicket.h"
#include "LastMinuteTicket.h"
#include "VIPTicket.h"

class TicketFactory {
public:
	static std::unique_ptr<Ticket> createTicket(const std::string& ticketTypeStr,
		const std::string& passengerName,
		const std::string& flightId,
		double baseFlightPrice);
};