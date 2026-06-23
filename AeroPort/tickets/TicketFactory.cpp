#include "TicketFactory.h"
#include "StandardStrategy.h"
#include "LastMinuteStrategy.h"
#include "VIPStrategy.h"

std::unique_ptr<IPricingStrategy> TicketFactory::createStrategy(
    const std::string& ticketTypeStr)
{
    if (ticketTypeStr == "Standard") {
        return std::make_unique<StandardStrategy>();
    } else if (ticketTypeStr == "LastMinute") {
        return std::make_unique<LastMinuteStrategy>();
    } else if (ticketTypeStr == "VIP") {
        return std::make_unique<VIPStrategy>();
    }
    return nullptr;
}

std::unique_ptr<Ticket> TicketFactory::createTicket(
    const std::string& ticketTypeStr,
    const std::string& passengerName,
    const std::string& flightId,
    double baseFlightPrice)
{
    auto strategy = createStrategy(ticketTypeStr);
    if (!strategy) return nullptr;

    return std::make_unique<Ticket>(passengerName, flightId,
                                    std::move(strategy), baseFlightPrice);
}
