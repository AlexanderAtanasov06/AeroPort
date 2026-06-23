#include "Ticket.h"

Ticket::Ticket(const std::string& passengerName, const std::string& flightID, std::unique_ptr<IPricingStrategy> strategy, double basePrice)
    : passengerName(passengerName), flightID(flightID), strategy(std::move(strategy)),
      paidPrice(this->strategy->calculatePrice(basePrice)), baggageWeight(0),
      remainingFreeBaggage(this->strategy->getFreeBaggage()) {
}

void Ticket::upgradeStrategy(std::unique_ptr<IPricingStrategy> newStrategy, double basePrice) {
    paidPrice = newStrategy->calculatePrice(basePrice);
    remainingFreeBaggage = newStrategy->getFreeBaggage();
    strategy = std::move(newStrategy);
}

double Ticket::calculateBaggageFee(double weight) const {
    if (weight > remainingFreeBaggage) {
        return (weight - remainingFreeBaggage) * BAGGAGE_FEE_PER_KILO_IN_EUR;
    }
    return 0;
}

void Ticket::addBaggage(double weight, double paid) {
    double requiredAmount = calculateBaggageFee(weight);
    if (paid < requiredAmount) {
        throw std::runtime_error("Insufficient funds for baggage fee.");
        return;
    }
    if (weight >= remainingFreeBaggage) {
        remainingFreeBaggage = 0;
    } else {
        remainingFreeBaggage -= weight;
    }
    baggageWeight += weight;
}

bool Ticket::isRefundable() const {
    return strategy->isRefundable();
}

double Ticket::getRefundAmount() const {
    return strategy->getRefundAmount(paidPrice);
}

std::string Ticket::getPassengerName() const {
    return passengerName;
}

std::string Ticket::getFlightID() const {
    return flightID;
}

double Ticket::getPrice() const {
    return paidPrice;
}

double Ticket::getBaggageWeight() const {
    return baggageWeight;
}

std::string Ticket::getTicketTypeStr() const
{
    return strategy->getName();
}
