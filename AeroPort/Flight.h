#pragma once
#include <string>
#include <vector>
#include "Airplane.h"
#include "Ticket.h"

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
	std::shared_ptr<Airplane> plane;
	std::string destination;
	double baseTicketPrice;
	std::vector<Ticket> soldTickets;
	Status status;
public:
	Flight(const std::string& flightID, std::shared_ptr<Airplane> plane, const std::string destination, double baseTicketPrice);

	std::string getFlightID() const;
	std::shared_ptr<Airplane> getAirplane() const;
	std::string getDestination() const;
	double getBaseTicketPrice() const;
	std::vector<Ticket> getSoldTickets() const;
	Status getStatus() const;
};