#include "ListRunwaysCommand.h"
#include "Engine.h"
#include <print>

void ListRunwaysCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void ListRunwaysCommand::visit(AirportAuthority& a) {
    std::println("[Error] This command is not available for System Administrator!");
}

void ListRunwaysCommand::visit(Dispatcher& d) {
    Engine& e = Engine::getInstance();
    const auto& runways = e.getRunways();

    std::println("Airport Runways Overview:");

    for (const auto& runway : runways) {
        std::print("- {} ({}m", runway->getRunwayID(), runway->getLength());

        if (!runway->isWithILS() && !runway->isWithHeavyDuty() && !runway->isWithVIP()) {
            std::print(", Basic");
        }
        else {
            if (runway->isWithILS()) std::print(", ILS");
            if (runway->isWithHeavyDuty()) std::print(", HeavyDuty");
            if (runway->isWithVIP()) std::print(", VIP");
        }
        std::print(") -> Status: ");

        auto status = runway->getStatus();
        if (status == Runway::Status::FREE) {
            std::println("Free");
        }
        else if (status == Runway::Status::MAINTENANCE) {
            std::println("Maintenance");
        }
        else if (status == Runway::Status::OCCUPIED) {
            std::print("Occupied");
            if (auto plane = runway->getAssignedPlane().lock()) {
                std::print(" (Aircraft ID: {})", plane->getID());
            }
            std::println();
        }
    }
}