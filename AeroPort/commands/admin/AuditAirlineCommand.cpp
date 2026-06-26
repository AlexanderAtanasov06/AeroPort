#include "AuditAirlineCommand.h"
#include "Engine.h"
#include <print>

AuditAirlineCommand::AuditAirlineCommand(const std::string& airlineName)
    : airlineName(airlineName) {
    if (airlineName.empty()) {
        throw std::invalid_argument("[Error] Airline name must not be empty!");
    }
}

void AuditAirlineCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void AuditAirlineCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void AuditAirlineCommand::visit(AirportAuthority& a) {
    Engine& e = Engine::getInstance();

    auto airline = e.findAirline(airlineName);

    if (!airline) {
        std::println("[Error] Airline '{}' not found!", airlineName);
        return;
    }

    size_t totalAircraft = airline->get().getAirplanes().size();
    size_t completedFlights = 0;
    size_t cancelledFlights = 0;

    for (const auto& flight : airline->get().getFlights()) {
        if (flight->getStatus() == Flight::Status::DEPARTED) {
            completedFlights++;
        }
        else if (flight->getStatus() == Flight::Status::CANCELLED) {
            cancelledFlights++;
        }
    }

    std::println("=== Airline Audit Report: {} ===", airlineName);
    std::println("Total Owned Aircraft: {}", totalAircraft);
    std::println("Completed Flights (Departed): {}", completedFlights);
    std::println("Cancelled Flights: {}", cancelledFlights);
    std::println("Current Corporate Balance: {:.2f} EUR", airline->get().getBalance());
}