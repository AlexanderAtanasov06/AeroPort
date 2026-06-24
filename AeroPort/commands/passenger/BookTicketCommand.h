#pragma once
#include <string>
#include "CommandVisitor.h"
#include "Passenger.h"
#include "Engine.h"

class BookTicketCommand : public CommandVisitor {
private:
    std::string flightId;
    std::string ticketType;

public:
    BookTicketCommand(const std::string& flightId, const std::string& ticketType);

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};
