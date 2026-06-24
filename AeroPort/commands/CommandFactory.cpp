#include "CommandFactory.h"

std::unique_ptr<CommandVisitor> CommandFactory::create(const std::string& line) {
	std::istringstream iss(line);
	std::string type;
	iss >> type;

	if (type == "undo") {
		return std::make_unique<UndoCommand>();
	}
	if (type == "assign-runway") {
		std::string flightID, runwayID;
		if (!(iss >> flightID >> runwayID)) {
			throw std::invalid_argument("[Error] Correct format: assign-runway <flight ID> <runway ID>");
		}
		return std::make_unique<AssignRunwayCommand>(flightID, runwayID);
	}
	if (type == "free-runway") {
		std::string runwayID;
		if (!(iss >> runwayID)) {
			throw std::invalid_argument("[Error] Correct format: free-runway <runway_id>");
		}
		return std::make_unique<FreeRunwayCommand>(runwayID);
	}
	if (type == "delay-flight") {
		std::string flightID;
		if (!(iss >> flightID)) {
			throw std::invalid_argument("[Error] Correct format: delay-flight <flight_id>");
		}
		return std::make_unique<DelayFlightCommand>(flightID);
	}

	if (type == "add-funds") {
		double funds;
		iss >> funds;
		return std::make_unique<AddFundsCommand>(funds);
	}
	if (type == "book-ticket") {
		std::string flightID, ticketType;
		if (!(iss >> flightID >> ticketType)) {
			throw std::invalid_argument("[Error] Correct format is: book-ticket <flight id> <ticket type>");
		}
		return std::make_unique<BookTicketCommand>(flightID, ticketType);
	}
	if (type == "list-flights") {
		std::string destination;
		if (!(iss >> destination)) {
			throw std::invalid_argument("[Error] Correct format is: list-flights <destination>");
		}
		return std::make_unique<ListFlightsCommand>(destination);
	}
	if (type == "schedule-flight") {
		return std::make_unique<ScheduleFlightCommand>(line);
	}
	if (type == "cancel-flight") {
		std::string id;
		iss >> id;
		return std::make_unique<CancelFlightCommand>(id);
	}
	if (type == "upgrade-ticket")
	{
		std::string flightID, newTicketType;
		if (!(iss >> flightID >> newTicketType))
		{
			throw std::invalid_argument("[Error] Correct format is: upgrade-ticket <flight ID> <new ticket type>");
		}
		return std::make_unique<UpgradeTicketCommand>(flightID, newTicketType);
	}
	if (type == "add-baggage") {
		std::string flightID;
		double weight;
		if (!(iss >> flightID >> weight)) {
			throw std::invalid_argument("[Error] Invalid arguments! Correct format is: add-baggage <flight ID> <weight>");
		}
		return std::make_unique<AddBaggageCommand>(flightID, weight);
	}
	if (type == "cancel-ticket") {
		std::string flightID;
		if (!(iss >> flightID)) {
			throw std::invalid_argument("[Error] Correct format is: cancel-ticket <flight id>");
		}
		return std::make_unique<CancelTicketCommand>(flightID);
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
