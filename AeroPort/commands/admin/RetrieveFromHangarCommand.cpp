#include "RetrieveFromHangarCommand.h"

RetrieveFromHangarCommand::RetrieveFromHangarCommand(size_t aircraftID)
	: aircraftID(aircraftID) {
	if (aircraftID < 0) {
		throw std::invalid_argument("[Error] Airplane ID must not be negative");
	}
}

void RetrieveFromHangarCommand::visit(AirportAuthority& a) {
	Engine& e = Engine::getInstance();

	auto hangarRef = e.findHangarByAircraftID(aircraftID);
	if (!hangarRef) {
		std::println("[Error] Aircraft ID: {} is not currently in any hangar!", aircraftID);
		return;
	}
	auto& hangar = hangarRef->get();

	auto aircraft = hangar.removeAircraft(aircraftID);
	aircraft->repair();

	std::println("[Success] Aircraft ID: {} retrieved from Hangar {}. Health restored to 100%.",
		aircraftID, hangar.getHangarID());
}
