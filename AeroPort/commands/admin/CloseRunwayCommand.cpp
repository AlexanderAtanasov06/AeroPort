#include "CloseRunwayCommand.h"

CloseRunwayCommand::CloseRunwayCommand(const std::string& id) : runwayID(id) {
	if (runwayID.empty()) {
		throw std::invalid_argument("[Error] Runway ID must not be empty!");
	}
}

void CloseRunwayCommand::visit(AirportAuthority& a) {
	Engine& e = Engine::getInstance();
	auto runway = e.findRunway(runwayID);

	if (!runway) {
		std::println("[Error] Runway not found!");
		return;
	}
	runway->setStatus(Runway::Status::MAINTENANCE);

	std::println("[System] Runway {} is now closed. Status -> Maintenance", runwayID);

	for (const auto& airline : e.getAirlines()) {
		for (const auto& flight : airline->getFlights()) {
			if (auto r = flight->getAssignedRunway().lock()) {
				if (r->getRunwayID() == runwayID) {
					flight->setStatus(Flight::Status::SCHEDULED);
					std::println("Flight {} status changed to scheduled", flight->getFlightID());
				}
			}
		}
	}
}

