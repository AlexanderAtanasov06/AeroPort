#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"

class ListAirspaceCommand : public CommandVisitor {
public:
    ListAirspaceCommand() = default;

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};