#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"

class ListAirspaceCommand : public CommandVisitor {
public:
    ListAirspaceCommand() = default;

    void visit(Dispatcher& d) override;
};