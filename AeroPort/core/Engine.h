#pragma once
#include "CommandFactory.h"
#include "WeatherSubject.h"
#include "User.h"
#include "Airline.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include "Hangar.h"
#include <string>
#include <memory>
#include <vector>
#include <print>
#include <optional>
#include <functional>
#include <sstream>

class Engine : public WeatherSubject {
private:
	Engine();
	bool isRunning;
	bool loaded;
	std::vector<std::string> commandHistory;
	double airportBalance;
	std::weak_ptr<User> currentUser;
	std::vector<std::shared_ptr<User>> users;
	std::vector<std::shared_ptr<Runway>> runways;
	std::vector<std::unique_ptr<Hangar>> hangars;
	std::vector<std::unique_ptr<Airline>> airlines;

	std::vector<std::shared_ptr<IWeatherObserver>> observers;

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
	void addHangar(std::unique_ptr<Hangar> hangar);
	void addAirline(std::unique_ptr<Airline> airline);

	std::optional<std::reference_wrapper<Airline>> findAirlineByAircraftID(size_t id) const;
	std::optional<std::reference_wrapper<Airline>> findAirline(const std::string& name) const;
	std::optional<std::reference_wrapper<Hangar>> findHangarByAircraftID(size_t id) const;
	std::shared_ptr<User> findUserByName(const std::string& name) const;
	std::shared_ptr<Runway> findRunway(const std::string& id) const;
	std::optional<std::reference_wrapper<Hangar>> findHangar(const std::string& id) const;

	const std::vector<std::shared_ptr<Runway>>& getRunways() const;
	const std::vector<std::unique_ptr<Airline>>& getAirlines() const;

	double getAirportBalance() const;
	void addAirportBalance(double amount);
	void deductAirportBalance(double amount);

	bool isAircraftInHangar(size_t aircraftID) const;
	bool isAircraftOnRunway(size_t aircraftID) const;

	void addObserver(std::shared_ptr<IWeatherObserver> observer) override;
	void notifyObservers(const std::string& weather) override;

	void loadState();
	void saveState() const;
};
