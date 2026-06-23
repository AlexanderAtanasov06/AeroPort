#pragma once
#include <string>
#include <memory>
#include "Ticket.h"
#include "IPricingStrategy.h"

class TicketFactory {
public:
    TicketFactory() = delete;

    static std::unique_ptr<Ticket> createTicket(
        const std::string& ticketTypeStr,
        const std::string& passengerName,
        const std::string& flightId,
        double baseFlightPrice
    );

    static std::unique_ptr<IPricingStrategy> createStrategy(
        const std::string& ticketTypeStr
    );
};
