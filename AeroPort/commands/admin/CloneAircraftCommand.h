#pragma once
#include "Engine.h"
#include "CommandVisitor.h"

class CloneAircraftCommand : public CommandVisitor {
    size_t airplaneID;
    size_t count;
    static constexpr double AIRCRAFT_PRICE = 10000.0;
public:
    CloneAircraftCommand(size_t airplaneID, size_t count);

    void visit(AirportAuthority& a) override;
};
