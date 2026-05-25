#include "Passenger.h"

Passenger::Passenger(const std::string& name, const std::string& pass)
	: User(name, pass, Role::PASSENGER) {
}

void Passenger::addFunds(double amount)
{
	funds += amount;
}
