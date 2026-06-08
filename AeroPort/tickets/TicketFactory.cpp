#include "TicketFactory.h"

std::unique_ptr<Ticket> TicketFactory::createTicket(const std::string& ticketTypeStr, const std::string& passengerName, const std::string& flightId, double baseFlightPrice) {
	if (ticketTypeStr == "Standard") {
		return std::make_unique<StandardTicket>(passengerName, flightId, baseFlightPrice);
	}
	else if (ticketTypeStr == "LastMinute") {
		return std::make_unique<LastMinuteTicket>(passengerName, flightId, baseFlightPrice);
	}
	else if (ticketTypeStr == "VIP") {
		return std::make_unique<VIPTicket>(passengerName, flightId, baseFlightPrice);
	}

	return nullptr;
}
