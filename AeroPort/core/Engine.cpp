#include "Engine.h"
#include <iostream>
#include <print>

Engine::Engine() : isRunning(true), activeUser(nullptr) {
	AirportAuthority& a = AirportAuthority::getInstance();
	admin = std::make_shared<AirportAuthority>(a);
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
		processCommand(input);
	}
	//save();
}

void Engine::processCommand(const std::string& line) {
	std::vector<std::string> args = splitArguments(line);
	std::string cmd = args[0];
	if (cmd == "login") {
		proccessLoginCommand(args);
	}
	else if (cmd == "register") {
		proccessRegisterCommand(args);
	}
	else if (cmd == "logout") {
		proccessLogoutCommand(args);
	}
	else if (activeUser) {

	}
	else {
		std::println("[System] You are not logged in!");
	}
}

void Engine::proccessRegisterCommand(std::vector<std::string> args) {
	if (args.size() != 4) {
		std::println("[Error] Invalid arguments! Correct format is: register <name> <password> <role>.");
		return;
	}

	std::string name = args[1];
	std::string pass = args[2];
	std::string role = args[3];

	//if (name.empty() || pass.empty() || role.empty()) {
	//	std::println("[Error] Invalid arguments! Correct format is: register <name> <password> <role>.");
	//	return;
	//}

	if (role == "Dispatcher") {
		dispatchers.emplace_back(std::make_shared<Dispatcher>(name, pass));
	}
	else if (role == "Passenger") {
		passengers.emplace_back(std::make_shared<Passenger>(name, pass));
	}
	else {
		std::println("[Error] Invalid role! Choose between Passenger and Dispatcher.");
	}
}

void Engine::proccessLoginCommand(std::vector<std::string> args) {
	if (args.size() != 3)
	{
		std::println("[Error] Invalid arguments! Correct format is: login <name> <password>.");
		return;
	}

	std::string name = args[1];
	std::string pass = args[2];

	//Look for user in users
}

void Engine::proccessLogoutCommand(std::vector<std::string> args) {
	if (args.size() != 1)
	{
		std::println("[System] Unrecognized command");
		return;
	}
	if (!activeUser) {
		std::println("[System] You are already logged out!");
	}
	else {
		activeUser->logout();
		activeUser = nullptr;
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
