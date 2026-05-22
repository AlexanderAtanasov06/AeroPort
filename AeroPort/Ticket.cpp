#include "Ticket.h"

Ticket::Ticket(const std::string& name, const std::string& flightID, TicketType type, double amount, double baggage) : passengerName(name), flightID(flightID), ticketType(type), paidAmount(amount), baggageWeight(baggage){}

std::string Ticket::getPassengerName() const {
	return passengerName;
}

std::string Ticket::getFlightId() const {
	return flightID;
}

double Ticket::getPaidAmount() const {
	return paidAmount;
}

double Ticket::getBaggageWeight() const {
	return baggageWeight;
}

Ticket::TicketType Ticket::getType() const {
	return ticketType;
}


