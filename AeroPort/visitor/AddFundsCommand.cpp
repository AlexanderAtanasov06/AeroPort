#include "AddFundsCommand.h"

AddFundsCommand::AddFundsCommand(double funds) : funds(funds){}

void AddFundsCommand::visit(Passenger& p) {
	p.addFunds(funds);
}

void AddFundsCommand::visit(Dispatcher& d) {
	std::println("[Error]");
}

void AddFundsCommand::visit(AirportAuthority& a) {
	std::println("[Error]");
}
