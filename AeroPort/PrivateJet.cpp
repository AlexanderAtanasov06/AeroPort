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

void PrivateJet::decreaseHealthAfterFlight() {
	if (health < HEALTH_DROP) {
		health = 0;
	}
	else {
		health -= HEALTH_DROP;
	}
}

std::unique_ptr<Airplane> PrivateJet::clone() const {
	return std::make_unique<PrivateJet>(this->model);
}

