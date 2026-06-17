#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include "IPricingStrategy.h"

class Ticket {
    static constexpr double BAGGAGE_FEE_PER_KILO_IN_EUR = 5.0;

    std::string passengerName;
    std::string flightID;
    std::unique_ptr<IPricingStrategy> strategy;
    double paidPrice;
    double baggageWeight;
    double remainingFreeBaggage;
    
public:
    Ticket(const std::string& passengerName,
           const std::string& flightID,
           std::unique_ptr<IPricingStrategy> strategy,
           double basePrice);

    Ticket(const Ticket&) = delete;
    Ticket& operator=(const Ticket&) = delete;

    Ticket(Ticket&&) = default;
    Ticket& operator=(Ticket&&) = default;

    void upgradeStrategy(std::unique_ptr<IPricingStrategy> newStrategy, double basePrice);

    double calculateBaggageFee(double weight) const;
    void addBaggage(double weight, double paid);

    bool isRefundable() const;
    double getRefundAmount() const;

    std::string getPassengerName() const;
    std::string getFlightId() const;
    double getPrice() const;
    double getBaggageWeight() const;
};
