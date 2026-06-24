#pragma once
#include <string>
#include <vector>
#include "Airplane.h";
#include "Flight.h"

class Airline{
	std::string name;
	double balance;
	std::vector<std::shared_ptr<Airplane>> fleet;
	std::vector<std::shared_ptr<Flight>> flights;
public:
	Airline(const std::string& name, double balance);

	std::shared_ptr<Airplane> findAirplane(size_t id) const;
	const std::vector<std::shared_ptr<Airplane>>& getAirplanes() const;

	std::shared_ptr<Flight> findFlight(const std::string& id) const;
	const std::vector<std::shared_ptr<Flight>>& getFlights() const;

	const std::string& getName() const;
	double getBalance() const;

	void deductBalance(double amount);
	void addBalance(double amount);

	void addAirplane(std::shared_ptr<Airplane> plane);
	void addFlight(std::shared_ptr<Flight> flight);
};