#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Engine.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"

class CancelTicketCommand : public CommandVisitor {
private:
    std::string flightId;

public:
    CancelTicketCommand(const std::string& flightId);

    void visit(Passenger& p) override;
};