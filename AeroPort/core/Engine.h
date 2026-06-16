#pragma once
#include "CommandFactory.h"
#include "User.h"
#include "Airline.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include "Hangar.h"
#include "Flight.h"
#include <string>
#include <memory>
#include <vector>
#include <print>
#include <sstream>

class Engine {
private:
	//std::shared_ptr<AirportAuthority> admin;

	Engine();
	bool isRunning;
	std::shared_ptr<User> currentUser;
	std::vector<std::shared_ptr<Runway>> runways;
	std::vector<std::shared_ptr<User>> users;
	std::vector<std::shared_ptr<Hangar>> hangars;
	std::vector<std::shared_ptr<Airline>> airlines;

	std::vector<std::string> splitArguments(const std::string& line);
	void proccessLogoutCommand(std::vector<std::string> args);
	void proccessLoginCommand(std::vector<std::string> args);
	void proccessRegisterCommand(std::vector<std::string> args);
	void processCommand(const std::string& line);
	
public:
	static Engine& getInstance();

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void run();

	void addRunway(std::shared_ptr<Runway> runway);
	void addHangar(std::shared_ptr<Hangar> hangar);
	void addAirline(std::shared_ptr<Airline> airline);

	std::shared_ptr<Airline> findAirlineByAircraftID(size_t id) const;
	std::shared_ptr<Runway> findRunway(const std::string& id) const;
	std::shared_ptr<Hangar> findHangar(const std::string& id) const;
	std::shared_ptr<Airline> findAirline(const std::string& name) const;

	const std::vector<std::shared_ptr<Runway>>& getRunways() const;
	const std::vector<std::shared_ptr<Airline>>& getAirlines() const;

	bool isAircraftInHangar(size_t aircraftID) const;
	bool isAircraftOnRunway(size_t aircraftID) const;
};
