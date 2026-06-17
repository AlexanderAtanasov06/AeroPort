#pragma once
#include "Airplane.h"
class CargoPlane : public Airplane {
	size_t loadCapacity;
	static constexpr size_t REQUIRED_RUNWAY_LENGTH = 3000;
	static constexpr size_t HEALTH_DROP = 45;
	static constexpr size_t AIRPORT_TAX_PER_TONNE_IN_EUR = 15;
public:
	CargoPlane(const std::string& model, size_t loadCapacity);

	std::string info() const override;
	size_t getRequiredRunwayLength() const override;
	bool requiresVIP() const override;
	bool requiresHeavyDuty() const override;
	void decreaseHealthAfterFlight() override;
	std::string getType() const override;
	size_t getCapacity() const override;

	std::unique_ptr<Airplane> clone() const override;

};