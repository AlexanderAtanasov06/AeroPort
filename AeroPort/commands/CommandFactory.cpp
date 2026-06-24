#include "CommandFactory.h"
#include <unordered_map>
#include <functional>
#include <stdexcept>

using CommandCreator = std::function<std::unique_ptr<CommandVisitor>(std::istringstream&, const std::string&)>;

std::unique_ptr<CommandVisitor> CommandFactory::create(const std::string& line) {
	std::istringstream iss(line);
	std::string type;
	iss >> type;

	static const std::unordered_map<std::string, CommandCreator> commandRegistry = {

		{"undo", [](std::istringstream&, const std::string&) {
			return std::make_unique<UndoCommand>();
		}},
		{"assign-runway", [](std::istringstream& iss, const std::string&) {
			std::string flightID, runwayID;
			if (!(iss >> flightID >> runwayID)) {
				throw std::invalid_argument("[Error] Correct format: assign-runway <flight ID> <runway ID>");
			}
			return std::make_unique<AssignRunwayCommand>(flightID, runwayID);
		}},
		{"free-runway", [](std::istringstream& iss, const std::string&) {
			std::string runwayID;
			if (!(iss >> runwayID)) {
				throw std::invalid_argument("[Error] Correct format: free-runway <runway_id>");
			}
			return std::make_unique<FreeRunwayCommand>(runwayID);
		}},
		{"delay-flight", [](std::istringstream& iss, const std::string&) {
			std::string flightID;
			if (!(iss >> flightID)) {
				throw std::invalid_argument("[Error] Correct format: delay-flight <flight_id>");
			}
			return std::make_unique<DelayFlightCommand>(flightID);
		}},

		{"add-funds", [](std::istringstream& iss, const std::string&) {
			double funds;
			iss >> funds;
			return std::make_unique<AddFundsCommand>(funds);
		}},
		{"book-ticket", [](std::istringstream& iss, const std::string&) {
			std::string flightID, ticketType;
			if (!(iss >> flightID >> ticketType)) {
				throw std::invalid_argument("[Error] Correct format is: book-ticket <flight id> <ticket type>");
			}
			return std::make_unique<BookTicketCommand>(flightID, ticketType);
		}},
		{"list-flights", [](std::istringstream& iss, const std::string&) {
			std::string destination;
			if (!(iss >> destination)) {
				throw std::invalid_argument("[Error] Correct format is: list-flights <destination>");
			}
			return std::make_unique<ListFlightsCommand>(destination);
		}},
		{"upgrade-ticket", [](std::istringstream& iss, const std::string&) {
			std::string flightID, newTicketType;
			if (!(iss >> flightID >> newTicketType)) {
				throw std::invalid_argument("[Error] Correct format is: upgrade-ticket <flight ID> <new ticket type>");
			}
			return std::make_unique<UpgradeTicketCommand>(flightID, newTicketType);
		}},
		{"add-baggage", [](std::istringstream& iss, const std::string&) {
			std::string flightID;
			double weight;
			if (!(iss >> flightID >> weight)) {
				throw std::invalid_argument("[Error] Invalid arguments! Correct format is: add-baggage <flight ID> <weight>");
			}
			return std::make_unique<AddBaggageCommand>(flightID, weight);
		}},
		{"cancel-ticket", [](std::istringstream& iss, const std::string&) {
			std::string flightID;
			if (!(iss >> flightID)) {
				throw std::invalid_argument("[Error] Correct format is: cancel-ticket <flight id>");
			}
			return std::make_unique<CancelTicketCommand>(flightID);
		}},

		{"schedule-flight", [](std::istringstream&, const std::string& fullLine) {
			return std::make_unique<ScheduleFlightCommand>(fullLine);
		}},
		{"cancel-flight", [](std::istringstream& iss, const std::string&) {
			std::string id;
			iss >> id;
			return std::make_unique<CancelFlightCommand>(id);
		}},
		{"build-runway", [](std::istringstream&, const std::string& fullLine) {
			return std::make_unique<BuildRunwayCommand>(fullLine);
		}},
		{"build-hangar", [](std::istringstream&, const std::string& fullLine) {
			return std::make_unique<BuildHangarCommand>(fullLine);
		}},
		{"close-runway", [](std::istringstream& iss, const std::string&) {
			std::string runwayID;
			iss >> runwayID;
			return std::make_unique<CloseRunwayCommand>(runwayID);
		}},
		{"register-airline", [](std::istringstream& iss, const std::string&) {
			std::string name;
			double balance;
			iss >> name >> balance;
			return std::make_unique<RegisterAirlineCommand>(name, balance);
		}},
		{"buy-aircraft", [](std::istringstream& iss, const std::string&) {
			std::string name, aircraftType, model;
			double capacity;
			if (!(iss >> name >> aircraftType >> model >> capacity)) {
				throw std::invalid_argument("[Error] Invalid arguments! Correct format is: buy-aircraft <airline name> <type> <model> <capacity/tonnage>");
			}
			return std::make_unique<BuyAircraftCommand>(name, aircraftType, model, capacity);
		}},
		{"clone-aircraft", [](std::istringstream& iss, const std::string&) {
			size_t id, count;
			if (!(iss >> id >> count)) {
				throw std::invalid_argument("[Error] Invalid arguments! Correct format is: clone-aircraft <id> <count>");
			}
			return std::make_unique<CloneAircraftCommand>(id, count);
		}},
		{"send-to-hangar", [](std::istringstream& iss, const std::string&) {
			size_t id;
			std::string hID;
			if (!(iss >> id >> hID)) {
				throw std::invalid_argument("[Error] Correct format: send-to-hangar <aircraft_id> <hangar_id>");
			}
			return std::make_unique<SendToHangarCommand>(id, hID);
		}},
		{"retrieve-from-hangar", [](std::istringstream& iss, const std::string&) {
			size_t id;
			iss >> id;
			return std::make_unique<RetrieveFromHangarCommand>(id);
		}}
	};

	auto it = commandRegistry.find(type);
	if (it != commandRegistry.end()) {
		return it->second(iss, line);
	}

	return nullptr;
}