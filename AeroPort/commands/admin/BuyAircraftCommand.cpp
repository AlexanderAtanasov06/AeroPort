#include "BuyAircraftCommand.h"

BuyAircraftCommand::BuyAircraftCommand(const std::string& airlineName, const std::string& type, const std::string& model, double capacityOrTonnage) : airlineName(airlineName), type(type), model(model), capacityOrTonnage(capacityOrTonnage) {
	if (capacityOrTonnage < 0) {
		throw std::invalid_argument("[Error] Capacity/Tonnage must be a positive number!");
	}
}

void BuyAircraftCommand::visit(Passenger& p) {
	std::println("[Error] This command is not available for Passenger!");
}

void BuyAircraftCommand::visit(Dispatcher& d) {
	std::println("[Error] This command is not available for Dispatcher!");
}

void BuyAircraftCommand::visit(AirportAuthority& a) {
	Engine& e = Engine::getInstance();

	auto airline = e.findAirline(airlineName);
	if (!airline) {
		std::println("[Error] Airline '{}' not found!", airlineName);
		return;
	}

	if (airline->get().getBalance() < AIRCRAFT_PRICE) {
		std::println("[Error] Airline '{}' has insufficient funds!", airlineName);
		return;
	}

	auto airplane = AirplaneFactory::create(type, model, capacityOrTonnage);
	if (!airplane) {
		std::println("[Error] Unknown airplane type! Choose between PassengerPlane, CargoPlane, PrivateJet.");
		return;
	}

	airline->get().deductBalance(AIRCRAFT_PRICE);

	std::println("[System] Purchased {}(ID: {}). {} balance : {:.2f} EUR.", airplane->getType(), airplane->getID() , airline->get().getName(), airline->get().getBalance());

	airline->get().addAirplane(std::move(airplane));
}