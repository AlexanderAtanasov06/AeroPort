#include "TicketFactory.h"
#include "StandardStrategy.h"
#include "LastMinuteStrategy.h"
#include "VIPStrategy.h"

std::unique_ptr<Ticket> TicketFactory::createTicket(
    const std::string& ticketTypeStr,
    const std::string& passengerName,
    const std::string& flightId,
    double baseFlightPrice)
{
    std::unique_ptr<IPricingStrategy> strategy;

    if (ticketTypeStr == "Standard") {
        strategy = std::make_unique<StandardStrategy>();
    } else if (ticketTypeStr == "LastMinute") {
        strategy = std::make_unique<LastMinuteStrategy>();
    } else if (ticketTypeStr == "VIP") {
        strategy = std::make_unique<VIPStrategy>();
    } else {
        return nullptr;
    }

    return std::make_unique<Ticket>(passengerName, flightId, std::move(strategy), baseFlightPrice);
}
