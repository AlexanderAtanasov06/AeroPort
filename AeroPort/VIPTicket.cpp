#include "VIPTicket.h"

VIPTicket::VIPTicket(const std::string& passengerName, const std::string& flightID, double baseFlightPrice)
	: Ticket(passengerName, flightID, Ticket::TicketType::VIP, baseFlightPrice * 2, 20) {
}

double VIPTicket::getRefundAmount() {
	return price;
}

bool VIPTicket::isRefundable() {
	return true;
}
