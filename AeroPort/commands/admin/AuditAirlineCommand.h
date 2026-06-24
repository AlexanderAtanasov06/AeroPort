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

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};