#include "Ticket.h"

Ticket::Ticket(const std::string& passengerName, const std::string& flightID, TicketType type, double price, double remainingFreeBaggage)
	: passengerName(passengerName), flightID(flightID), ticketType(type), price(price), baggageWeight(0), remainingFreeBaggage(remainingFreeBaggage) {
}

double Ticket::calculateBaggageFee(double weight) const {
	if (weight > remainingFreeBaggage) {
		return (weight - remainingFreeBaggage) * BAGGAGE_FEE_PER_KILO_IN_EUR;
	}
	else {
		return 0;
	}
}

void Ticket::addBaggage(double weight, double paid) {
	double requiredAmount = calculateBaggageFee(weight);
	if (paid < requiredAmount)
	{
		//throw
		return;
	}
	if (weight >= remainingFreeBaggage)
	{
		remainingFreeBaggage = 0;
	}
	else
	{
		remainingFreeBaggage -= weight;
	}
	baggageWeight += weight;
}

double Ticket::getTicketPrice() const {
	return price;
}

std::string Ticket::getPassengerName() const {
	return passengerName;
}

std::string Ticket::getFlightId() const {
	return flightID;
}

double Ticket::getPrice() const {
	return price;
}

double Ticket::getBaggageWeight() const {
	return baggageWeight;
}

Ticket::TicketType Ticket::getType() const {
	return ticketType;
}


