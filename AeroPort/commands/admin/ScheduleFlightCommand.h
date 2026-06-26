#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include <string>

class ScheduleFlightCommand : public CommandVisitor {
    std::string commandLine;
public:
    ScheduleFlightCommand(const std::string& commandLine);

    void visit(AirportAuthority& a) override;
};
