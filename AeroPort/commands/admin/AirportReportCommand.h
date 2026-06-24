#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"

class AirportReportCommand : public CommandVisitor {
public:
    AirportReportCommand() = default;

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};