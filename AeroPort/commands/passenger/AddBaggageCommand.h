#pragma once
#include <string>
#include "CommandVisitor.h"
#include "Passenger.h"

class AddBaggageCommand : public CommandVisitor {
private:
    std::string flightId;
    double weight;

public:
    AddBaggageCommand(const std::string& flightId, double weight);

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};