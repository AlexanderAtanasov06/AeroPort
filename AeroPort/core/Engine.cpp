#include <fstream>
#include <io.h>
#include <stdio.h>
#include "Engine.h"
#include <iostream>
#include <print>

Engine::Engine() : isRunning(true), loaded(false), airportBalance(0) {
	users.push_back(AirportAuthority::getInstance());
}

Engine& Engine::getInstance() {
	static Engine e;
	return e;
}

void Engine::run() {
	std::string input;
	while (isRunning) {
		std::print("> ");
		std::getline(std::cin, input);
		if (input.empty()) continue;
		if (input == "exit") break;
		try {
			processCommand(input);
			commandHistory.push_back(input);
		}
		catch (std::invalid_argument& e) {
			std::println("{}", e.what());
		}
		catch (std::exception& e) {
			std::println("{}", e.what());
		}
	}
	saveState();
}

void Engine::proccessRegisterCommand(std::vector<std::string> args) {
	if (args.size() != 4) {
		std::println("[Error] Invalid arguments! Correct format is: register <name> <password> <role>.");
		return;
	}

	std::string name = args[1];
	std::string pass = args[2];
	std::string role = args[3];

	if (name.empty() || pass.empty() || role.empty()) {
		std::println("[Error] Invalid arguments! Correct format is: register <name> <password> <role>.");
		return;
	}

	for (const auto& user : users) {
		if (user->getName() == name) {
			std::println("[Error] Username is taken!");
			return;
		}
	}

	if (role == "Dispatcher") {
		users.emplace_back(std::make_shared<Dispatcher>(name, pass));
	}
	else if (role == "Passenger") {
		users.emplace_back(std::make_shared<Passenger>(name, pass));
	}
	else {
		std::println("[Error] Invalid role! Choose between Passenger and Dispatcher.");
		return;
	}
	std::println("[System] User '{}' registered succesfully (Role: {})", name, role);
}

void Engine::proccessLoginCommand(std::vector<std::string> args) {
	if (args.size() != 3) {
		std::println("[Error] Invalid arguments! Correct format is: login <name> <password>.");
		return;
	}
	bool success = false;
	std::string name = args[1];
	std::string pass = args[2];

	for (const auto& user : users) {
		if (user->getName() == name && user->checkPassword(pass)) {
			currentUser = user;
			success = true;
			break;
		}
	}
	if (!success) {
		std::println("[Error] Invalid username or password!");
		return;
	}
	std::println("[System] Successfully logged in {}. (Role: {}).", name, currentUser.lock()->getRoleStr());
}

void Engine::processCommand(const std::string& line) {
	std::vector<std::string> args = splitArguments(line);
	if (args.empty()) return;
	std::string cmd = args[0];

	if (currentUser.lock() && (cmd == "login" || cmd == "register")) {
		std::println("[Error] You are already logged in! Please logout first.");
		return;
	}
	if (cmd == "login") {
		proccessLoginCommand(args);
		return;
	}
	else if (cmd == "register") {
		proccessRegisterCommand(args);
		return;
	}
	else if (cmd == "logout") {
		proccessLogoutCommand(args);
		return;
	}
	else if (cmd == "save") {
		saveState();
		return;
	}
	else if (cmd == "load") {
		loadState();
		return;
	}
	if (!currentUser.lock()) {
		std::println("[Error] You are not logged in!");
		return;
	}

	if (cmd == "help") { currentUser.lock()->help(); return; }
	if (cmd == "view-profile") { currentUser.lock()->viewProfile(); return; }

	auto visitor = CommandFactory::create(line);
	if (!visitor) {
		std::println("[Error] Unknown command!");
		return;
	}
	currentUser.lock()->accept(*visitor);
}

void Engine::proccessLogoutCommand(std::vector<std::string> args) {
	if (args.size() != 1) {
		std::println("[System] Unrecognized command");
		return;
	}
	if (!currentUser.lock()) {
		std::println("[System] You are already logged out!");
	}
	else {
		currentUser.lock()->logout();
		currentUser.reset();
	}
}

std::vector<std::string> Engine::splitArguments(const std::string& line) {
	std::vector<std::string> v;
	std::istringstream iss(line);
	std::string word;
	while (iss >> word) {
		v.push_back(word);
	}
	return v;
}

void Engine::addRunway(std::shared_ptr<Runway> runway) {
	runways.push_back(runway);
}

void Engine::addHangar(std::unique_ptr<Hangar> hangar) {
	hangars.push_back(std::move(hangar));
}

void Engine::addAirline(std::unique_ptr<Airline> airline) {
	airlines.push_back(std::move(airline));
}

std::optional<std::reference_wrapper<Airline>> Engine::findAirlineByAircraftID(size_t id) const {
	for (const auto& airline : airlines) {
		auto airplane = airline->findAirplane(id);
		if (airplane) {
			return std::ref(*airline);
		}
	}
	return std::nullopt;
}

std::optional<std::reference_wrapper<Hangar>> Engine::findHangarByAircraftID(size_t id) const {
	for (const auto& hangar : hangars) {
		auto airplane = hangar->findAirplane(id);
		if (airplane) {
			return std::ref(*hangar);
		}
	}
	return std::nullopt;
}

std::shared_ptr<User> Engine::findUserByName(const std::string& name) const {
	auto it = std::find_if(users.begin(), users.end(), [&name](const auto& user) {
		return user->getName() == name;
		});
	if (it != users.end()) {
		return *it;
	}
	return nullptr;
}

std::shared_ptr<Runway> Engine::findRunway(const std::string& id) const {
	auto it = std::find_if(runways.begin(), runways.end(), [&id](const auto& runway) {
		return runway->getRunwayID() == id;
		});
	if (it != runways.end()) {
		return *it;
	}
	return nullptr;
}

std::optional<std::reference_wrapper<Hangar>> Engine::findHangar(const std::string& id) const {
	auto it = std::find_if(hangars.begin(), hangars.end(), [&id](const auto& hangar) {
		return hangar->getHangarID() == id;
		});
	if (it != hangars.end()) {
		return std::ref(**it);
	}
	return std::nullopt;
}

std::optional<std::reference_wrapper<Airline>> Engine::findAirline(const std::string& name) const {
	auto it = std::find_if(airlines.begin(), airlines.end(), [&name](const auto& airline) {
		return airline->getName() == name;
		});
	if (it != airlines.end()) {
		return std::ref(**it);
	}
	return std::nullopt;
}

const std::vector<std::shared_ptr<Runway>>& Engine::getRunways() const {
	return runways;
}

const std::vector<std::unique_ptr<Airline>>& Engine::getAirlines() const {
	return airlines;
}

double Engine::getAirportBalance() const {
	return airportBalance;
}

void Engine::addAirportBalance(double amount) {
	if (amount <= 0) {
		throw std::logic_error("[Error] Addition amount must be a positive number!");
	}
	airportBalance += amount;
}

void Engine::deductAirportBalance(double amount) {
	if (amount >= airportBalance) {
		throw std::logic_error("[Error] Deduction amount is higher than the airline's balance!");
	}
	airportBalance -= amount;
}

bool Engine::isAircraftInHangar(size_t aircraftID) const {
	for (const auto& hangar : hangars) {
		for (const auto& plane : hangar->getPlanes()) {
			if (plane->getID() == aircraftID) return true;
		}
	}
	return false;
}

bool Engine::isAircraftOnRunway(size_t aircraftID) const {
	for (const auto& runway : runways) {
		if (auto p = runway->getAssignedPlane().lock()) {
			if (p->getID() == aircraftID) {
				return true;
			}
		}
	}
	return false;
}

void Engine::addObserver(std::shared_ptr<IWeatherObserver> observer) {
	observers.push_back(observer);
}

void Engine::notifyObservers(const std::string& weather) {
	for (const auto& obs : observers) {
		obs->onWeatherChange(weather);
	}
}

void Engine::loadState() {
	if (loaded) {
		std::println("[Error] Previously saved state is already loaded from file!");
		return;
	}

	fflush(stdout);
	int originalStdout = _dup(_fileno(stdout));
	auto dummy = freopen("NUL", "w", stdout);

	std::ifstream file("aeroport_data.txt");
	
	if (!file) {
		std::ofstream create_file("aeroport_data.txt");

		if (!create_file) {
			throw std::runtime_error("[Error] Cannot create application state file!");
		}
	}

	int count = 0;
	std::string line;
	while (std::getline(file, line)) {
		processCommand(line);
		commandHistory.push_back(line);
		count++;
	}

	fflush(stdout);
	auto d = _dup2(originalStdout, _fileno(stdout));
	_close(originalStdout);

	if (!count) {
		std::println("[Error] No saved application state found!");
		return;
	}
	std::println("[System] State successfully loaded in background!");
	loaded = true;
}

void Engine::saveState() const {
	std::ofstream file("aeroport_data.txt");
	if (!file) {
		throw std::runtime_error("[Error] Cannot save current state!");
	}
	for (const auto& cmd : commandHistory) {
		if (cmd != "save" && cmd != "load") {
			file << cmd << "\n";
		}
	}
	file << "logout" << "\n";
	std::println("[System] AeroPort application state successfully serialized and saved to 'aeroport_data.txt'");
}

