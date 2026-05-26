#pragma once
#include <string>
#include <memory>
#include "Airplane.h"

class Runway {
public:
	enum class Status {
		FREE,
		OCCUPIED,
		MAINTENANCE
	};
private:
	std::string runwayID;
	int length;
	bool hasILS = false;
	bool hasVIP = false;
	bool hasHeavyDuty = false;
	std::weak_ptr<Airplane> plane;
public:
	Runway(const std::string& runwayID, int length);
};