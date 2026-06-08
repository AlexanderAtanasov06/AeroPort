#include "LastMinuteTicket.h"

LastMinuteTicket::LastMinuteTicket(const std::string& passengerName, const std::string& flightID, double baseFlightPrice)
	: Ticket(passengerName, flightID, Ticket::TicketType::LAST_MINUTE, baseFlightPrice / 2, 0) {
}

double LastMinuteTicket::getRefundAmount() {
	return 0;
}

bool LastMinuteTicket::isRefundable() {
	return false;
}
