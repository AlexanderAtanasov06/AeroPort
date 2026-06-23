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

	const std::string& getRunwayID() const;
	int getLength() const;
	bool isWithILS() const;
	bool isWithHeavyDuty() const;
	bool isWithVIP() const;
	bool isOccupied() const;
	std::shared_ptr<Airplane> getAssignedPlane() const;

	void setStatus(Status status);
	void setAssignedPlane(std::shared_ptr<Airplane> airplane);
	void clearAssignedPlane();
private:
	std::string runwayID;
	int length;
	bool hasILS = false;
	bool hasVIP = false;
	bool hasHeavyDuty = false;
	std::weak_ptr<Airplane> plane;
	Status runwayStatus;

	Runway(const std::string& runwayID, int length, bool hasILS, bool hasVIP, bool hasHeavyDuty);
};