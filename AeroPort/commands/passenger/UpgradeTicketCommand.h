#pragma once
#include "CommandVisitor.h"
#include "TicketFactory.h"
#include "Engine.h"

class UpgradeTicketCommand : public CommandVisitor {
    std::string flightId;
    std::string newTicketType;

public:
    UpgradeTicketCommand(const std::string& flightId, const std::string& newTicketType);

    void visit(Passenger& p);
    void visit(Dispatcher& d);
    void visit(AirportAuthority& a);
};
