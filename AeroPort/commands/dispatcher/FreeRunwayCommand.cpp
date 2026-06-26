#include "FreeRunwayCommand.h"

FreeRunwayUndoAction::FreeRunwayUndoAction(const std::string& fID, const std::string& rID, const std::string& aName,
	Flight::Status fStatus, double airlineRevenue, double airportRevenue, int health)
	: flightID(fID), runwayID(rID), airlineName(aName), prevFlightStatus(fStatus),
	airlineRevenueAdded(airlineRevenue), airportRevenueAdded(airportRevenue), healthDeducted(health) {
}

void FreeRunwayUndoAction::undo() {
	Engine& e = Engine::getInstance();

	auto airlineOpt = e.findAirline(airlineName);
	Airline& airline = airlineOpt->get();

	std::shared_ptr<Flight> flight = nullptr;
	if (airlineOpt) {
		flight = airline.findFlight(flightID);
	}
	auto runway = e.findRunway(runwayID);

	if (flight && runway && airlineOpt) {
		flight->setStatus(prevFlightStatus);
		flight->setAssignedRunway(runway);

		auto airplane = flight->getAirplane().lock();
		runway->setStatus(Runway::Status::OCCUPIED);
		runway->setAssignedPlane(airplane);

		airline.addBalance(-airlineRevenueAdded);
		if (airplane) {
			airplane->increaseHealth(healthDeducted);
		}

		std::println("[System] Reverting last command (free-runway)...");
		std::println("[System] Flight {} reverted to {}. Runway {} re-occupied. Funds ({} EUR) and Health reverted.",
			flightID, flight->getStatusStr(), runwayID, airlineRevenueAdded);
	}
	else {
		std::println("[Error] Undo failed: Required entities no longer exist.");
	}
}

FreeRunwayCommand::FreeRunwayCommand(const std::string& runwayID) : runwayID(runwayID) {
	if (runwayID.empty()) {
		throw std::invalid_argument("[Error] Runway ID must not be empty!");
	}
}

void FreeRunwayCommand::visit(Dispatcher& d) {
	Engine& e = Engine::getInstance();

	auto runway = e.findRunway(runwayID);
	if (!runway) {
		std::println("[Error] Runway '{}' not found!", runwayID);
		return;
	}

	if (!runway->isOccupied()) {
		std::println("[Error] Runway {} is already FREE. No flight to dispatch.", runwayID);
		return;
	}

	std::shared_ptr<Flight> activeFlight = nullptr;
	Airline* activeAirline = nullptr;
	for (const auto& airline : e.getAirlines()) {
		for (const auto& flight : airline->getFlights()) {
			auto assignedRunway = flight->getAssignedRunway().lock();
			if (assignedRunway == runway && flight->getStatus() == Flight::Status::BOARDING) {
				activeFlight = flight;
				activeAirline = airline.get();
				break;
			}
		}
		if (activeFlight) break;
	}

	if (!activeFlight || !activeAirline) {
		std::println("[Error] Inconsistent State: Runway is occupied but no corresponding BOARDING flight was found!");
		return;
	}

	auto airplane = activeFlight->getAirplane().lock();
	if (!airplane) {
		std::println("[Error] Flight {} has no valid airplane assigned!", activeFlight->getFlightID());
		return;
	}

	auto prevStatus = activeFlight->getStatus();

	double airlineRevenue = 0;
	for (const auto& ticket : activeFlight->getSoldTickets()) {
		airlineRevenue += ticket->getPrice();
	}
	double airportRevenue = 0;
	std::string type = airplane->getType();
	if (type == "PassengerPlane") {
		airportRevenue = 0.1 * airlineRevenue;
	}
	else if (type == "CargoPlane") {
		airportRevenue = airplane->getCapacity() * 15;
	}
	else if (type == "PrivateJet") {
		airportRevenue = 5000;
	}
	else {
		throw std::logic_error("[Error] Invalid airplane type");
	}

	airlineRevenue -= airportRevenue;

	activeAirline->addBalance(airlineRevenue);
	e.addAirportBalance(airportRevenue);
	int healthCost = airplane->decreaseHealthAfterFlight();

	activeFlight->setStatus(Flight::Status::DEPARTED);
	activeFlight->setAssignedRunway(nullptr);

	runway->setStatus(Runway::Status::FREE);
	runway->clearAssignedPlane();

	std::println("[Success] Runway {} is now FREE. Flight {} has DEPARTED.", runwayID, activeFlight->getFlightID());
	std::println("[System] Airline {} earned {} EUR. Airplane health reduced by {}.",
		activeAirline->getName(), airlineRevenue, healthCost);

	d.addUndoAction(std::make_unique<FreeRunwayUndoAction>(
		activeFlight->getFlightID(), runwayID, activeAirline->getName(), prevStatus, airlineRevenue, airportRevenue, healthCost
	));
}