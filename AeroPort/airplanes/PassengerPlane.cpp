#include "PassengerPlane.h"
PassengerPlane::PassengerPlane(const std::string& model, size_t capacity) : Airplane(model), capacity(capacity) {}

std::string PassengerPlane::info() const {
	return std::format("Passenger plane (ID: {}) - Health: {}%", ID, health);
}

size_t PassengerPlane::getRequiredRunwayLength() const {
	return REQUIRED_RUNWAY_LENGTH;
}

bool PassengerPlane::requiresVIP() const {
	return false;
}

bool PassengerPlane::requiresHeavyDuty() const {
	return false;
}

size_t PassengerPlane::decreaseHealthAfterFlight() {
	if (health < HEALTH_DROP) {
		health = 0;
	}
	else {
		health -= HEALTH_DROP;
	}
	return HEALTH_DROP;
}

std::unique_ptr<Airplane> PassengerPlane::clone() const {
	return std::make_unique<PassengerPlane>(this->model, this->capacity);
}

size_t PassengerPlane::getAirportTax() const {
	return AIRPORT_TAX_OF_SOLD_TICKETS_IN_PERCANTAGE;
}

std::string PassengerPlane::getType() const {
	return "PassengerPlane";
}

size_t PassengerPlane::getCapacity() const {
	return capacity;
}

