#include "CloneAircraftCommand.h"

CloneAircraftCommand::CloneAircraftCommand(size_t airplaneID, size_t count)
    : airplaneID(airplaneID), count(count) {
    if (count <= 0) {
        throw std::invalid_argument("[Error] Clone count must be at least 1!");
    }
}

void CloneAircraftCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void CloneAircraftCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void CloneAircraftCommand::visit(AirportAuthority& a) {
    Engine& e = Engine::getInstance();
    
    auto airline = e.findAirlineByAircraftID(airplaneID);
    if (!airline) {
        std::println("[Error] No aircraft with ID {} found in any airline!", airplaneID);
        return;
    }

    auto plane = airline->findAirplane(airplaneID);
    if (!plane) {
        std::println("[Error] Aircraft with ID {} not found!", airplaneID);
        return;
    }

    double totalCost = AIRCRAFT_PRICE * count;

    if (airline->getBalance() < totalCost) {
        std::println("[Error] Insufficient funds! {} balance: {:.2f} EUR. Required: {:.2f} EUR.",
            airline->getName(), airline->getBalance(), totalCost);
        return;
    }

    for (size_t i = 0; i < count; i++) {
        auto clone = plane->clone();
        size_t newID = clone->getID();
        airline->addAirplane(std::move(clone));
        airline->deductBalance(AIRCRAFT_PRICE);
        std::println("[System] Aircraft ID: {} successfully cloned. New Aircraft ID: {}. {} balance: {:.2f} EUR.",
            airplaneID, newID, airline->getName(), airline->getBalance());
    }
}
