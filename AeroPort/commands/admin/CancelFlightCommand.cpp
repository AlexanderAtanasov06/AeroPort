#include "CancelFlightCommand.h"
#include "Engine.h"
#include <print>

CancelFlightCommand::CancelFlightCommand(const std::string& flightID)
	: flightID(flightID) {
	if (flightID.empty()) {
		throw std::invalid_argument("[Error] Flight ID must not be empty!");
	}
}

void CancelFlightCommand::visit(AirportAuthority& a) {
	Engine& e = Engine::getInstance();
	std::shared_ptr<Flight> flight = nullptr;

	for (const auto& airline : e.getAirlines()) {
		auto f = airline->findFlight(flightID);
		if (f) {
			flight = f;
			break;
		}
	}

	if (!flight) {
		std::println("[Error] Flight '{}' does not exist!", flightID);
		return;
	}

	if (flight->getStatus() == Flight::Status::DEPARTED) {
		std::println("[Error] Flight {} has already Departed. It cannot be cancelled.", flightID);
		return;
	}
	if (flight->getStatus() == Flight::Status::CANCELLED) {
		std::println("[Error] Flight {} is already Cancelled.", flightID);
		return;
	}

	if (flight->getStatus() == Flight::Status::BOARDING) {
		auto runway = flight->getAssignedRunway();
		if (runway.lock()) {
			runway.lock()->setStatus(Runway::Status::FREE);
			runway.lock()->clearAssignedPlane();
		}
	}

	std::println("[System] Auto-refunding passengers for flight {}...", flightID);
	for (const auto& ticket : flight->getSoldTickets()) {
		std::shared_ptr<User> user = e.findUserByName(ticket->getPassengerName());
		RefundTicketVisitor refund(ticket->getPassengerName(), ticket->getFlightID());
		if (user) {
			user->accept(refund);
		}
	}

	flight->setStatus(Flight::Status::CANCELLED);
	std::println("[System] Flight {} has been Cancelled.", flightID);
}
