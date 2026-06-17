#pragma once
#include <string>
#include <memory>
#include "Ticket.h"

class TicketFactory {
public:
    TicketFactory() = delete;
    
    static std::unique_ptr<Ticket> createTicket(
        const std::string& ticketTypeStr,
        const std::string& passengerName,
        const std::string& flightId,
        double baseFlightPrice
    );
};
