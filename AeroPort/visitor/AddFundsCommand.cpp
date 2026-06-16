#include "AddFundsCommand.h"

AddFundsCommand::AddFundsCommand(double funds) : funds(funds) {
	if (funds <= 0) {
		throw std::invalid_argument("[Error] Funds should be a positive number!");
	}
}

void AddFundsCommand::visit(Passenger& p) {
	p.addFunds(funds);
	std::println("[System] Funds added successfully. New balance: {:.2f} EUR", p.getBalance());
}

void AddFundsCommand::visit(Dispatcher& d) {
	std::println("[Error] This command is not available for Dispatcher!");
}

void AddFundsCommand::visit(AirportAuthority& a) {
	std::println("[Error] This command is not available for System Administrator!");
}
