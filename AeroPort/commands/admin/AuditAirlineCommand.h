#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include <string>

class AuditAirlineCommand : public CommandVisitor {
private:
    std::string airlineName;
public:
    AuditAirlineCommand(const std::string& airlineName);

    void visit(AirportAuthority& a) override;
};