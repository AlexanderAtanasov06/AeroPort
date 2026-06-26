#include "CommandVisitor.h"

void CommandVisitor::visit(Passenger& p) {
	std::println("[Error] This command is not available for Passenger!");
}
void CommandVisitor::visit(AirportAuthority& p) {
	std::println("[Error] This command is not available for Airport Authority!");
}
void CommandVisitor::visit(Dispatcher& p) {
	std::println("[Error] This command is not available for Dispatcher!");
}