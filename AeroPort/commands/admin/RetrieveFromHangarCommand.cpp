#include "RetrieveFromHangarCommand.h"

RetrieveFromHangarCommand::RetrieveFromHangarCommand(size_t aircraftID)
	: aircraftID(aircraftID) {
	if (aircraftID < 0) {
		throw std::invalid_argument("[Error] Airplane ID must not be negative");
	}
}

void RetrieveFromHangarCommand::visit(Passenger& p) {
	std::println("[Error] This command is not available for Passenger!");
}

void RetrieveFromHangarCommand::visit(Dispatcher& d) {
	std::println("[Error] This command is not available for Dispatcher!");
}

void RetrieveFromHangarCommand::visit(AirportAuthority& a) {
	Engine& e = Engine::getInstance();

	auto hangar = e.findHangarByAircraftID(aircraftID);
	if (!hangar) {
		std::println("[Error] Aircraft ID: {} is not currently in any hangar!", aircraftID);
		return;
	}

	auto aircraft = hangar->removeAircraft(aircraftID);
	aircraft->repair();

	std::println("[Success] Aircraft ID: {} retrieved from Hangar {}. Health restored to 100%.",
		aircraftID, hangar->getHangarID());
}
