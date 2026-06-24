#include "ListFlightsCommand.h"
#include "Engine.h"
#include <print>

ListFlightsCommand::ListFlightsCommand(const std::string& destination) : destination(destination) {}

void ListFlightsCommand::visit(Passenger& p) {
	const auto& airlines = Engine::getInstance().getAirlines();

	std::println("Available flights to {}:", destination);

	int count = 0;
	for (const auto& airline : airlines) {
		for (const auto& flight : airline->getFlights()) {
			if (flight->getDestination() == destination &&
				(flight->getStatus() == Flight::Status::SCHEDULED ||
					flight->getStatus() == Flight::Status::DELAYED)) {
				count++;
				std::println("{}. {} | Status: {} | Base Price: {:.2f} EUR", count, flight->getFlightID(),
					flight->getStatusStr(), flight->getBaseTicketPrice());
			}
		}
	}

	if (count == 0) {
		std::println("[System] No available flights to {}.", destination);
	}
}

void ListFlightsCommand::visit(Dispatcher& d) {
	std::println("[Error] This command is not available for Dispatcher!");
}

void ListFlightsCommand::visit(AirportAuthority& a) {
	std::println("[Error] This command is not available for System Administrator!");
}
