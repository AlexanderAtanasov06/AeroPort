#include "DelayFlightCommand.h"

DelayFlightUndoAction::DelayFlightUndoAction(const std::string& fID, Flight::Status status)
    : flightID(fID), prevStatus(status) {
}

void DelayFlightUndoAction::undo() {
    Engine& e = Engine::getInstance();

    std::shared_ptr<Flight> flight = nullptr;
    for (const auto& airline : e.getAirlines()) {
        flight = airline->findFlight(flightID);
        if (flight) break;
    }

    if (flight) {
        flight->setStatus(prevStatus);
        std::println("[System] Reverting last command (delay-flight)...");
        std::println("[System] Flight {} status reverted to {}.", flightID, flight->getStatusStr());
    }
    else {
        std::println("[Error] Undo failed: Flight '{}' no longer exists.", flightID);
    }
}

DelayFlightCommand::DelayFlightCommand(const std::string& flightID) : flightID(flightID) {
    if (flightID.empty()) {
        throw std::invalid_argument("[Error] Flight ID must not be empty!");
    }
}

void DelayFlightCommand::visit(Dispatcher& d) {
    Engine& e = Engine::getInstance();

    std::shared_ptr<Flight> flight = nullptr;
    for (const auto& airline : e.getAirlines()) {
        flight = airline->findFlight(flightID);
        if (flight) break;
    }

    if (!flight) {
        std::println("[Error] Flight '{}' not found!", flightID);
        return;
    }

    auto currentStatus = flight->getStatus();

    if (currentStatus == Flight::Status::DELAYED) {
        std::println("[Error] Flight {} is already DELAYED.", flightID);
        return;
    }

    if (currentStatus == Flight::Status::DEPARTED || currentStatus == Flight::Status::CANCELLED) {
        std::println("[Error] Cannot delay flight {} because its status is {}.", flightID, flight->getStatusStr());
        return;
    }

    if (currentStatus == Flight::Status::BOARDING) {
        std::println("[Error] Flight {} is currently BOARDING on a runway. Free the runway first!", flightID);
        return;
    }

    auto prevStatus = flight->getStatus();

    flight->setStatus(Flight::Status::DELAYED);
    std::println("[Success] Flight {} is now DELAYED.", flightID);

    d.addUndoAction(std::make_unique<DelayFlightUndoAction>(flightID, prevStatus));
}