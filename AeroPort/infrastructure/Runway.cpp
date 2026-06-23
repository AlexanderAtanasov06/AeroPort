#include "Runway.h"

Runway::Runway(const std::string& runwayID, int length) 
	: runwayID(runwayID), length(length), runwayStatus(Runway::Status::FREE) {
}

Runway::Runway(const std::string& runwayID, int length, bool hasILS, bool hasVIP, bool hasHeavyDuty)
	: runwayID(runwayID), length(length),
	hasILS(hasILS), hasVIP(hasVIP), hasHeavyDuty(hasHeavyDuty), runwayStatus(Runway::Status::FREE) {
}

Runway::Builder::Builder(const std::string& runwayID, int length) 
	: runwayID(runwayID), length(length) {
}

Runway::Builder& Runway::Builder::withILS() {
	hasILS = true;
	return *this;
}

Runway::Builder& Runway::Builder::withVIP() {
	hasVIP = true;
	return *this;
}

Runway::Builder& Runway::Builder::withHeavyDuty() {
	hasHeavyDuty = true;
	return *this;
}

Runway Runway::Builder::build() {
	return Runway(runwayID, length, hasILS, hasVIP, hasHeavyDuty);
}

const std::string& Runway::getRunwayID() const {
	return runwayID;
}

int Runway::getLength() const {
	return length;
}

bool Runway::isWithILS() const {
	return hasILS;
}

bool Runway::isWithHeavyDuty() const {
	return hasHeavyDuty;
}

bool Runway::isWithVIP() const {
	return hasVIP;
}

bool Runway::isOccupied() const {
	return !plane.expired();
}

std::shared_ptr<Airplane> Runway::getAssignedPlane() const {
	return plane.lock();
}

void Runway::setStatus(Status status) {
	this->runwayStatus = status;
}

void Runway::setAssignedPlane(std::shared_ptr<Airplane> airplane) {
	this->plane = airplane;
}

void Runway::clearAssignedPlane() {
	plane.reset();
}
