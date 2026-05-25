#include "Flight.h"

Flight::Flight(const std::string& flightID, std::shared_ptr<Airplane> plane, const std::string destination, double baseTicketPrice)
 : flightID(flightID), plane(plane), destination(destination), baseTicketPrice(baseTicketPrice), status(Status::SCHEDULED) {
}

std::string Flight::getFlightID() const
{
	return flightID;
}

std::shared_ptr<Airplane> Flight::getAirplane() const
{
	return plane;
}

std::string Flight::getDestination() const
{
	return destination;
}

double Flight::getBaseTicketPrice() const
{
	return baseTicketPrice;
}

std::vector<Ticket> Flight::getSoldTickets() const
{
	return soldTickets;
}

Flight::Status Flight::getStatus() const
{
	return status;
}

