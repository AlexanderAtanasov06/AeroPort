#include "BuildHangarCommand.h"

BuildHangarCommand::BuildHangarCommand(const std::string& commandLine) : commandLine(commandLine) {}

void BuildHangarCommand::visit(Passenger& p) {
	std::println("[Error] This command is not available for Passenger!");
}

void BuildHangarCommand::visit(Dispatcher& d) {
	std::println("[Error] This command is not available for Dispatcher!");
}

void BuildHangarCommand::visit(AirportAuthority& a) {
	std::istringstream iss(commandLine);
	std::string command, id;
	size_t capacity;
	double fee;

	if (!(iss >> command >> id >> capacity >> fee)  || fee <= 0) {
		std::println("[Error] Invalid arguments! Correct format is: build-hangar <hangar ID> <capacity> <repair fee>");
		return;
	}

	Engine& e = Engine::getInstance();
	if (e.findHangar(id)) {
		std::println("[Error] A hangar with this ID already exists!");
		return;
	}

	std::unique_ptr<Hangar> hangar = std::make_unique<Hangar>(id, capacity, fee);
	e.addHangar(std::move(hangar));
	std::println("[System] Hangar {} built successfully (Capacity: {}, Repair Fee: {:.2f} EUR)", id, capacity, fee);
}
