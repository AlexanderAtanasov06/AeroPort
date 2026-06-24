#include "SendToHangarCommand.h"

SendToHangarCommand::SendToHangarCommand(size_t aircraftID, const std::string& hangarID)
    : aircraftID(aircraftID), hangarID(hangarID) {
}

void SendToHangarCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void SendToHangarCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void SendToHangarCommand::visit(AirportAuthority& a) {
    Engine& e = Engine::getInstance();

    auto airline = e.findAirlineByAircraftID(aircraftID);
    if (!airline) {
        std::println("[Error] No aircraft with ID {} found in any airline!", aircraftID);
        return;
    }

    auto aircraft = airline->findAirplane(aircraftID);
    if (!aircraft) {
        std::println("[Error] Aircraft with ID {} not found!", aircraftID);
        return;
    }

    if (e.isAircraftInHangar(aircraftID)) {
        std::println("[Error] Aircraft ID: {} is already in a hangar!", aircraftID);
        return;
    }

    if (e.isAircraftOnRunway(aircraftID)) {
        std::println("[Error] Aircraft ID: {} is currently assigned to a runway and cannot be sent to a hangar!", aircraftID);
        return;
    }

    auto hangar = e.findHangar(hangarID);
    if (!hangar) {
        std::println("[Error] Hangar '{}' does not exist!", hangarID);
        return;
    }

    if (hangar->isFull()) {
        std::println("[Error] Hangar {} is at maximum capacity ({}/{} slots occupied)!",
            hangarID, hangar->getCurrentCount(), hangar->getCapacity());
        return;
    }

    double fee = hangar->getRepairFee();
    if (airline->getBalance() < fee) {
        std::println("[Error] Insufficient funds! {} balance: {:.2f} EUR. Repair fee: {:.2f} EUR.",
            airline->getName(), airline->getBalance(), fee);
        return;
    }

    hangar->addAircraft(aircraft);
    airline->deductBalance(fee);

    std::println("[Success] Aircraft ID: {} admitted to Hangar {}. {:.2f} EUR deducted from {} balance.",
        aircraftID, hangarID, fee, airline->getName());
}
