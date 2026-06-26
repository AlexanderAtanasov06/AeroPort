#include "ListFleetCommand.h"
#include "Engine.h"
#include <print>

ListFleetCommand::ListFleetCommand(const std::string& airlineName) : airlineName(airlineName) {
    if (airlineName.empty()) {
        throw std::invalid_argument("[Error] Airline name cannot be empty!");
    }
}

void ListFleetCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void ListFleetCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void ListFleetCommand::visit(AirportAuthority& a) {
    Engine& e = Engine::getInstance();
    auto airline = e.findAirline(airlineName);

    if (!airline) {
        std::println("[Error] Airline '{}' not found!", airlineName);
        return;
    }

    std::println("Fleet Overview for {}:", airlineName);
    
    const auto& fleet = airline->get().getAirplanes();
    if (fleet.empty()) {
        std::println("[System] {} has no airplanes in its fleet.", airlineName);
        return;
    }

    int count = 1;
    for (const auto& airplane : fleet) {
        std::println("{}. {}", count++, airplane->info());
    }
}