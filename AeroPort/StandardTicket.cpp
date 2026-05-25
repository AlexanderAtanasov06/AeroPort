#include "StandardTicket.h"

StandardTicket::StandardTicket(const std::string& passengerName, const std::string& flightID, double baseFlightPrice)
	: Ticket(passengerName, flightID, Ticket::TicketType::STANDARD, baseFlightPrice, 0) {
}

double StandardTicket::getRefundAmount() {
	return price;
}

bool StandardTicket::isRefundable() {
	return true;
}
