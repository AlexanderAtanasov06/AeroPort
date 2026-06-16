#pragma once
#include "Airplane.h"
class PassengerPlane : public Airplane {
private:
	size_t capacity;
	static constexpr size_t REQUIRED_RUNWAY_LENGTH = 2000;
	static constexpr size_t HEALTH_DROP = 35;
	static constexpr size_t AIRPORT_TAX_OF_SOLD_TICKETS_IN_PERCANTAGE = 10;
public:
	PassengerPlane(const std::string& model, size_t capacity);

	std::string info() const override;
	size_t getRequiredRunwayLength() const override;
	bool requiresVIP() const override;
	bool requiresHeavyDuty() const override;
	void decreaseHealthAfterFlight() override;
	std::string getType() const;

	std::unique_ptr<Airplane> clone() const override;
};
