#include "MyTicketsCommand.h"
#include "Engine.h"
#include <print>

void MyTicketsCommand::visit(Passenger& p) {
    const auto& tickets = p.getTickets();

    std::println("Your active tickets:");

    if (tickets.empty()) {
        std::println("[System] You have no active tickets.");
        return;
    }

    Engine& e = Engine::getInstance();
    int count = 1;

    for (const auto& ticket : tickets) {
        std::string flightID = ticket->getFlightID();
        std::string statusStr = "Unknown";

        for (const auto& airline : e.getAirlines()) {
            auto flight = airline->findFlight(flightID);
            if (flight) {
                statusStr = flight->getStatusStr();
                break;
            }
        }

        std::println("{}. Flight: {} | Type: {} | Paid: {:.2f} EUR | Baggage: {} kg | Status: {}",
            count++,
            flightID,
            ticket->getTicketTypeStr(),
            ticket->getPrice(),
            ticket->getBaggageWeight(),
            statusStr
        );
    }
}

void MyTicketsCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void MyTicketsCommand::visit(AirportAuthority& a) {
    std::println("[Error] This command is not available for System Administrator!");
}