#include "FilterFlightsCommand.h"
#include "Engine.h"
#include <print>

FilterFlightsCommand::FilterFlightsCommand(double maxPrice) : maxPrice(maxPrice) {
    if (maxPrice <= 0) {
        throw std::invalid_argument("[Error] Max price must be a positive number!");
    }
}

void FilterFlightsCommand::visit(Passenger& p) {
    Engine& e = Engine::getInstance();

    std::println("Filtered flights (Price < {:.2f} EUR):", maxPrice);

    int count = 1;
    for (const auto& airline : e.getAirlines()) {
        for (const auto& flight : airline->getFlights()) {
            auto status = flight->getStatus();
            if (status == Flight::Status::SCHEDULED || status == Flight::Status::DELAYED) {
                if (flight->getBaseTicketPrice() < maxPrice) {
                    std::println("{}. {} ({}) - {:.2f} EUR", 
                        count++, 
                        flight->getFlightID(), 
                        flight->getDestination(), 
                        flight->getBaseTicketPrice()
                    );
                }
            }
        }
    }

    if (count == 1) {
        std::println("[System] No flights found under {:.2f} EUR.", maxPrice);
    }
}

void FilterFlightsCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void FilterFlightsCommand::visit(AirportAuthority& a) {
    std::println("[Error] This command is not available for System Administrator!");
}