#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"

class FilterFlightsCommand : public CommandVisitor {
private:
    double maxPrice;
public:
    FilterFlightsCommand(double maxPrice);

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};