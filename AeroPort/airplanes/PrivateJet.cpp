#include "PrivateJet.h"

PrivateJet::PrivateJet(const std::string& model) : Airplane(model) {}

std::string PrivateJet::info() const {
	return std::format("Private Jet (ID: {}) - Health: {}%", ID, health);
}

size_t PrivateJet::getRequiredRunwayLength() const {
	return REQUIRED_RUNWAY_LENGTH;
}

bool PrivateJet::requiresVIP() const {
	return true;
}

bool PrivateJet::requiresHeavyDuty() const {
	return false;
}

size_t PrivateJet::decreaseHealthAfterFlight() {
	if (health < HEALTH_DROP) {
		health = 0;
	}
	else {
		health -= HEALTH_DROP;
	}
	return HEALTH_DROP;
}

std::string PrivateJet::getType() const {
	return "PrivateJet";
}

size_t PrivateJet::getCapacity() const {
	return CAPACITY;
}

std::unique_ptr<Airplane> PrivateJet::clone() const {
	return std::make_unique<PrivateJet>(this->model);
}

size_t PrivateJet::getAirportTax() const {
	return AIRPORT_TAX_IN_EUR;
}

