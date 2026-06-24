#include "SetWeatherCommand.h"
#include "Engine.h"
#include <sstream>
#include <print>

SetWeatherCommand::SetWeatherCommand(const std::string& commandLine)
    : commandLine(commandLine) {
}

void SetWeatherCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void SetWeatherCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void SetWeatherCommand::visit(AirportAuthority& a) {
    std::istringstream iss(commandLine);
    std::string command, weatherStr;

    if (!(iss >> command >> weatherStr) ||
        (weatherStr != "SUNNY" && weatherStr != "STORM")) {
        std::println("[Error] Invalid arguments! Correct format is: set-weather <SUNNY / STORM>");
        return;
    }

    Engine& e = Engine::getInstance();

    std::println("[ALERT] Global Weather Conditions changed to {}!", weatherStr);

    if (weatherStr == "STORM") {
        std::println("[Observer] Verifying airport infrastructure for safe landing conditions...");

        bool hasILS = false;
        for (const auto& runway : e.getRunways()) {
            if (runway->isWithILS() && runway->getStatus() == Runway::Status::FREE) {
                hasILS = true;
                break;
            }
        }
        if (!hasILS) {
            std::println("[System] WARNING: No active runways with ILS available!");
        }
    }

    e.notifyObservers(weatherStr);
}