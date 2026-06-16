#include "Runway.h"

Runway::Runway(const std::string& runwayID, int length) 
	: runwayID(runwayID), length(length) {
}

Runway::Runway(const std::string& runwayID, int length, bool hasILS, bool hasVIP, bool hasHeavyDuty)
	: runwayID(runwayID), length(length),
	hasILS(hasILS), hasVIP(hasVIP), hasHeavyDuty(hasHeavyDuty) {
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
