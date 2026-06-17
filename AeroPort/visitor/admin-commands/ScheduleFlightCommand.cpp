#include "ScheduleFlightCommand.h"
#include "Engine.h"
#include <sstream>
#include <print>

ScheduleFlightCommand::ScheduleFlightCommand(const std::string& commandLine) : commandLine(commandLine) {}

void ScheduleFlightCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void ScheduleFlightCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void ScheduleFlightCommand::visit(AirportAuthority& a) {
    std::istringstream iss(commandLine);
    std::string command, flightID, destination;
    size_t aircraftID;
    double basePrice;

    if (!(iss >> command >> flightID >> aircraftID >> destination >> basePrice) || basePrice <= 0) {
        std::println("[Error] Invalid arguments! Correct format is: schedule-flight <flight id> <aircraft ID> <destination> <base price>");
        return;
    }

    Engine& e = Engine::getInstance();

    for (const auto& airline : e.getAirlines()) {
        if (airline->findFlight(flightID)) {
            std::println("[Error] A flight with ID '{}' already exists!", flightID);
            return;
        }
    }

    std::shared_ptr<Airline> ownerAirline = e.findAirlineByAircraftID(aircraftID);
    if (!ownerAirline) {
        std::println("[Error] No aircraft with ID {} found in any airline!", aircraftID);
        return;
    }

    std::shared_ptr<Airplane> airplane = ownerAirline->findAirplane(aircraftID);

    if (!airplane->isHealthy()) {
        std::println("[Error] Aircraft ID {} has insufficient health ({}%). Send it to a hangar first!", aircraftID, airplane->getHealth());
        return;
    }

    if (e.isAircraftInHangar(aircraftID)) {
        std::println("[Error] Aircraft ID {} is currently in a hangar!", aircraftID);
        return;
    }

    if (e.isAircraftOnRunway(aircraftID)) {
        std::println("[Error] Aircraft ID {} is currently assigned to a runway!", aircraftID);
        return;
    }

    std::shared_ptr<Flight> flight = std::make_shared<Flight>(flightID, airplane, destination, basePrice);
    ownerAirline->addFlight(flight);

    std::println("[System] {} Flight {} to {} is now Scheduled.", airplane->getType(), flightID, destination);
}
