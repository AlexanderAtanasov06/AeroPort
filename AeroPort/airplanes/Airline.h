#pragma once
#include <string>
#include <vector>
#include "Airplane.h";
#include "Flight.h"

class Airline{
	std::string name;
	double balance;
	std::vector<std::shared_ptr<Airplane>> fleet;
	std::vector<Flight> flights;
};