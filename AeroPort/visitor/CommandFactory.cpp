#include "CommandFactory.h"

std::unique_ptr<CommandVisitor> CommandFactory::create(const std::string& line) {
	std::istringstream iss(line);
	std::string type;
	iss >> type;

	if (type == "add-funds") {
		double funds;
		iss >> funds;
		return std::make_unique<AddFundsCommand>(funds);
	}
	
	if (type == "build-runway") {
		return std::make_unique<BuildRunwayCommand>(line);
	}
	if (type == "build-hangar") {
		return std::make_unique<BuildHangarCommand>(line);
	}
	if (type == "close-runway") {
		std::string runwayID;
		iss >> runwayID;
		return std::make_unique<CloseRunwayCommand>(runwayID);
	}
	if (type == "register-airline") {
		std::string name;
		double balance;
		iss >> name >> balance;
		return std::make_unique<RegisterAirlineCommand>(name, balance);
	}
	if (type == "buy-aircraft") {
		std::string name, aircraftType, model;
		double capacity;
		if (!(iss >> name >> aircraftType >> model >> capacity)) {
			throw std::invalid_argument("[Error] Invalid arguments! Correct format is: buy-aircraft <airline name> <type> <model> <capacity/tonnage>");
		}
		return std::make_unique<BuyAircraftCommand>(name, aircraftType, model, capacity);
	}
	if (type == "clone-aircraft") {
		size_t id, count;
		if (!(iss >> id >> count)) {
			throw std::invalid_argument("[Error] Invalid arguments! Correct format is: clone-aircraft <id> <count>");
		}
		return std::make_unique<CloneAircraftCommand>(id, count);
	}
	if (type == "send-to-hangar") {
		size_t id;
		std::string hID;
		if (!(iss >> id >> hID)) {
			throw std::invalid_argument("[Error] Correct format: send-to-hangar <aircraft_id> <hangar_id>");
		}
		return std::make_unique<SendToHangarCommand>(id, hID);
	}
	if (type == "retrieve-from-hangar") {
		size_t id;
		iss >> id;
		return std::make_unique<RetrieveFromHangarCommand>(id);
	}

	return nullptr;
}

std::vector<std::string> CommandFactory::splitArguments(const std::string& line) {
	std::vector<std::string> v;
	std::istringstream iss(line);
	std::string word;
	while (iss >> word) {
		v.push_back(word);
	}
	return v;
}
