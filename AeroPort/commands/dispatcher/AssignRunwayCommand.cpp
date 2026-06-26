#include "AssignRunwayCommand.h"

AssignRunwayUndoAction::AssignRunwayUndoAction(const std::string& fID, const std::string& rID, Flight::Status status)
    : flightID(fID), runwayID(rID), prevStatus(status) {
}

void AssignRunwayUndoAction::undo() {
    Engine& e = Engine::getInstance();

    std::shared_ptr<Flight> flight = nullptr;
    for (const auto& airline : e.getAirlines()) {
        flight = airline->findFlight(flightID);
        if (flight) break;
    }
    auto runway = e.findRunway(runwayID);

    if (flight && runway) {
        flight->setStatus(prevStatus);
        flight->setAssignedRunway(nullptr);
        runway->setStatus(Runway::Status::FREE);
        runway->clearAssignedPlane();

        std::println("[System] Reverting last command (assign-runway)...");
        std::println("[System] Flight {} status reverted to {}. Runway {} reverted to Free.",
            flightID, flight->getStatusStr(), runwayID);
    }
    else {
        std::println("[Error] Undo failed: Flight or Runway no longer exists.");
    }
}

AssignRunwayCommand::AssignRunwayCommand(const std::string& flightID, const std::string& runwayID)
    : flightID(flightID), runwayID(runwayID) {
    if (flightID.empty() || runwayID.empty()) {
        throw std::invalid_argument("[Error] Flight ID and Runway ID must not be empty!");
    }
}

void AssignRunwayCommand::visit(Dispatcher& d) {
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

    if (flight->getStatus() != Flight::Status::SCHEDULED && flight->getStatus() != Flight::Status::DELAYED) {
        std::println("[Error] Flight {} is not ready for runway assignment (Current status: {})!", flightID, flight->getStatusStr());
        return;
    }

    auto runway = e.findRunway(runwayID);
    if (!runway) {
        std::println("[Error] Runway '{}' not found!", runwayID);
        return;
    }

    if (runway->isOccupied()) {
        std::println("[Error] Runway {} is currently Occupied by another aircraft!", runwayID);
        return;
    }

    auto airplane = flight->getAirplane().lock();
    if (!airplane) {
        std::println("[Error] Flight {} has no assigned airplane!", flightID);
        return;
    }

    bool isValid = true;
    std::string missingFlags = "";

    if (runway->getLength() < airplane->getRequiredRunwayLength()) {
        isValid = false;
        missingFlags += std::format("Length {}m < {}m. ", runway->getLength(), airplane->getRequiredRunwayLength());
    }
    if (airplane->requiresHeavyDuty() && !runway->isWithHeavyDuty()) {
        isValid = false;
        missingFlags += "Missing HeavyDuty flag. ";
    }
    if (airplane->requiresVIP() && !runway->isWithVIP()) {
        isValid = false;
        missingFlags += "Missing VIP flag. ";
    }

    if (!isValid) {
        std::println("[Error] Runway {} does not meet aircraft requirements! ({})", runwayID, missingFlags);
        return;
    }

    auto prevFlightStatus = flight->getStatus();

    flight->setStatus(Flight::Status::BOARDING);
    flight->setAssignedRunway(runway);
    runway->setStatus(Runway::Status::OCCUPIED);
    runway->setAssignedPlane(airplane);

    std::println("[Success] Flight {} assigned to {}. Status -> Boarding. Runway {} -> Occupied.", flightID, runwayID, runwayID);

    d.addUndoAction(std::make_unique<AssignRunwayUndoAction>(flightID, runwayID, prevFlightStatus));
}