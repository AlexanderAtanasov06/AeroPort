#include "Airline.h"

Airline::Airline(const std::string& name, double balance)
	: name(name), balance(balance) {
}

std::shared_ptr<Airplane> Airline::findAirplane(size_t id) const {
	auto it = std::find_if(fleet.begin(), fleet.end(), [&id](const auto& plane) {
		return plane->getID() == id;
		});
	if (it != fleet.end()) {
		return *it;
	}
	return nullptr;
}

const std::vector<std::shared_ptr<Airplane>>& Airline::getAirplanes() const {
	return fleet;
}

std::shared_ptr<Flight> Airline::findFlight(const std::string& id) const {
	auto it = std::find_if(flights.begin(), flights.end(), [&id](const auto& flight) {
		return flight->getFlightID() == id;
		});
	if (it != flights.end()) {
		return *it;
	}
	return nullptr;
}

const std::vector<std::shared_ptr<Flight>>& Airline::getFlights() const {
	return flights;
}

const std::string& Airline::getName() const {
	return name;
}

double Airline::getBalance() const {
	return balance;
}

void Airline::deductBalance(double amount) {
	balance -= amount;
}

void Airline::addAirplane(std::shared_ptr<Airplane> plane) {
	fleet.push_back(plane);
}

void Airline::addFlight(std::shared_ptr<Flight> flight) {
	flights.push_back(flight);
}

