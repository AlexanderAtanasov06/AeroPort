#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include "RefundVisitor.h"
#include <string>

class CancelFlightCommand : public CommandVisitor {
    std::string flightID;
public:
    CancelFlightCommand(const std::string& flightID);

    void visit(AirportAuthority& a) override;
};
