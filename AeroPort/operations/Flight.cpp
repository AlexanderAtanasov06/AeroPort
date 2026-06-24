#include "Flight.h"

Flight::Flight(const std::string& flightID, std::shared_ptr<Airplane> plane, const std::string destination, double baseTicketPrice)
	: flightID(flightID), plane(plane), destination(destination), baseTicketPrice(baseTicketPrice), status(Status::SCHEDULED) {
}

std::string Flight::getFlightID() const {
	return flightID;
}

std::weak_ptr<Airplane> Flight::getAirplane() const {
	return plane;
}

std::string Flight::getDestination() const {
	return destination;
}

double Flight::getBaseTicketPrice() const {
	return baseTicketPrice;
}

const std::vector<std::shared_ptr<Ticket>>& Flight::getSoldTickets() const {
	return soldTickets;
}

Flight::Status Flight::getStatus() const {
	return status;
}

std::string Flight::getStatusStr() const {
	switch (status) {
	case Status::SCHEDULED:
		return "Scheduled";
	case Status::BOARDING:
		return "Boarding";
	case Status::DELAYED:
		return "Delayed";
	case Status::DEPARTED:
		return "Departed";
	case Status::CANCELLED:
		return "Cancelled";
	default:
		return "Unknown";
	}
}

std::weak_ptr<Runway> Flight::getAssignedRunway() const {
	return assignedRunway;
}

bool Flight::hasAvailableSeats() const {
	return plane.lock()->getCapacity() > soldTickets.size();
}

void Flight::setStatus(Status status) {
	this->status = status;
}

void Flight::setAssignedRunway(std::shared_ptr<Runway> runway) {
	assignedRunway = runway;
}

void Flight::addTicket(std::shared_ptr<Ticket> ticket) {
	soldTickets.push_back(ticket);
}

void Flight::removeTicket(const std::shared_ptr<Ticket>& ticket) {
	std::erase(soldTickets, ticket);
}

