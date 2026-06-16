#pragma once
#include "CommandVisitor.h"
#include "Passenger.h"

class AddFundsCommand : public CommandVisitor {
private:
	double funds;
public:
	AddFundsCommand(double funds);
	void visit(Passenger& p) override;
	void visit(Dispatcher& d) override;
	void visit(AirportAuthority& a) override;
};