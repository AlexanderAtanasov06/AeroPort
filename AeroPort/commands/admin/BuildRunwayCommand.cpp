#include "BuildRunwayCommand.h"

BuildRunwayCommand::BuildRunwayCommand(const std::string& commandLine) : commandLine(commandLine) {
}

void BuildRunwayCommand::visit(Passenger& p) {
	std::println("[Error] This command is not available for Passenger!");
}

void BuildRunwayCommand::visit(Dispatcher& d) {
	std::println("[Error] This command is not available for Dispatcher!");
}

void BuildRunwayCommand::visit(AirportAuthority& a) {
	std::istringstream iss(commandLine);
	std::string command;
	std::string id;
	int length;

	std::string errorMessage = "[Error] Invalid arguments! Correct format is: build-runway <runway ID> <length> [ILS] [VIP] [HeavyDuty]. Last three parameters are optional!";

	if (!(iss >> command >> id >> length)) {
		std::println("{}", errorMessage);
		return;
	}

	Runway::Builder builder(id, length);

	Engine& e = Engine::getInstance();
	if (e.findRunway(id)) {
		std::println("[Error] A runway with this ID already exists!");
		return;
	}

	std::string flag;
	while (iss >> flag) {
		if (flag == "ILS") {
			builder.withILS();
		}
		else if (flag == "HeavyDuty") {
			builder.withHeavyDuty();
		}
		else if (flag == "VIP") {
			builder.withVIP();
		}
		else {
			std::println("{}", errorMessage);
			return;
		}
	}
	std::unique_ptr<Runway> runway = std::make_unique<Runway>(builder.build());

	std::print("[System] Runway {} ({}m", id, length);
	if (!runway->isWithILS() && !runway->isWithHeavyDuty() && !runway->isWithVIP()) {
		std::print(", Basic");
	}
	else {
		if (runway->isWithILS()) std::print(", ILS");
		if (runway->isWithHeavyDuty()) std::print(", HeavyDuty");
		if (runway->isWithVIP()) std::print(", VIP Terminal");
	}
	std::println(") built successfully");
	e.addRunway(std::move(runway));
}
