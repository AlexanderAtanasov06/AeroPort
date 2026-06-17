#pragma once
#include <string>
#include <vector>
#include "Airplane.h"
#include "Ticket.h"
#include "Runway.h"

class Flight {
public:
	enum class Status {
		SCHEDULED,
		BOARDING,
		DELAYED,
		DEPARTED,
		CANCELLED
	};
private:
	std::string flightID;
	std::weak_ptr<Airplane> plane;
	std::string destination;
	double baseTicketPrice;
	std::vector<std::shared_ptr<Ticket>> soldTickets;
	Status status;
	std::shared_ptr<Runway> assignedRunway;
public:
	Flight(const std::string& flightID, std::shared_ptr<Airplane> plane, const std::string destination, double baseTicketPrice);

	void setStatus(Status status);
	void setAssignedRunway(std::shared_ptr<Runway> runway);

	void addTicket(std::shared_ptr<Ticket> ticket);

	std::string getFlightID() const;
	std::weak_ptr<Airplane> getAirplane() const;
	std::string getDestination() const;
	double getBaseTicketPrice() const;
	const std::vector<std::shared_ptr<Ticket>>& getSoldTickets() const;
	Status getStatus() const;
	std::string getStatusStr() const;
	std::shared_ptr<Runway> getAssignedRunway() const;

	bool hasAvailableSeats() const;
};