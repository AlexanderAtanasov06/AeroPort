#include "CargoPlane.h"

CargoPlane::CargoPlane(const std::string& model, size_t loadCapacity) : Airplane(model), loadCapacity(loadCapacity) {}

std::string CargoPlane::info() const {
	return std::format("Cargo plane (ID: {}) - Health: {}%", ID, health);
}

size_t CargoPlane::getRequiredRunwayLength() const {
	return REQUIRED_RUNWAY_LENGTH;
}

bool CargoPlane::requiresVIP() const {
	return false;
}

bool CargoPlane::requiresHeavyDuty() const {
	return true;
}

size_t CargoPlane::decreaseHealthAfterFlight() {
	if (health < HEALTH_DROP) {
		health = 0;
	}
	else {
		health -= HEALTH_DROP;
	}
	return HEALTH_DROP;
}

std::string CargoPlane::getType() const {
	return "CargoPlane";
}

size_t CargoPlane::getCapacity() const {
	return loadCapacity;
}

std::unique_ptr<Airplane> CargoPlane::clone() const {
	return std::make_unique<CargoPlane>(this->model, this->loadCapacity);
}

size_t CargoPlane::getAirportTax() const {
	return AIRPORT_TAX_PER_TONNE_IN_EUR;
}
