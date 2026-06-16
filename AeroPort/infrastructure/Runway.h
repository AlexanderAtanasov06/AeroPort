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
	Runway(const std::string& runwayID, int length);

	class Builder {
	private:
		std::string runwayID;
		int length;
		bool hasILS = false;
		bool hasVIP = false;
		bool hasHeavyDuty = false;

	public:
		Builder(const std::string& runwayID, int length);
		Builder& withILS();
		Builder& withVIP();
		Builder& withHeavyDuty();
		Runway build();
	};
private:
	std::string runwayID;
	int length;
	bool hasILS = false;
	bool hasVIP = false;
	bool hasHeavyDuty = false;
	std::weak_ptr<Airplane> plane;

	Runway(const std::string& runwayID, int length, bool hasILS, bool hasVIP, bool hasHeavyDuty);
};