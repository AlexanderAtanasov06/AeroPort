#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include <string>

class FlightRevenueCommand : public CommandVisitor {
    std::string flightID;
public:
    FlightRevenueCommand(const std::string& flightID);

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};