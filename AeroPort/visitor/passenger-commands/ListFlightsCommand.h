#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"
#include <string>

class ListFlightsCommand : public CommandVisitor {
private:
	std::string destination;
public:
	ListFlightsCommand(const std::string& destination);

	void visit(Passenger& p) override;
	void visit(Dispatcher& d) override;
	void visit(AirportAuthority& a) override;
};
