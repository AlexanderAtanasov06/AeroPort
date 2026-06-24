#pragma once
#include "Airplane.h"

class PrivateJet : public Airplane {

	static constexpr size_t CAPACITY = 12;
	static constexpr size_t REQUIRED_RUNWAY_LENGTH = 1000;
	static constexpr size_t HEALTH_DROP = 25;
	static constexpr size_t AIRPORT_TAX_IN_EUR = 5000;
public:
	PrivateJet(const std::string& model);

	std::string info() const override;
	size_t getRequiredRunwayLength() const override;
	bool requiresVIP() const override;
	bool requiresHeavyDuty() const override;
	size_t decreaseHealthAfterFlight() override;
	std::string getType() const override;
	size_t getCapacity() const override;
	size_t getAirportTax() const override;

	std::unique_ptr<Airplane> clone() const override;

};
