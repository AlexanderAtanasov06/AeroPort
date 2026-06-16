#include "Engine.h"
#include <iostream>
#include <print>

Engine::Engine() : isRunning(true), currentUser(nullptr) {
	AirportAuthority& a = AirportAuthority::getInstance();
	admin = std::make_shared<AirportAuthority>(a);
	users.push_back(admin);
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
		}
		catch (std::invalid_argument& e) {
			std::println("{}", e.what());
		}
		catch (std::exception e) {
			std::println("{}", e.what());
		}
	}
	//save();
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
	std::println("[System] Successfully logged in {}. (Role: {}).", name, currentUser->getRoleStr());
}

void Engine::processCommand(const std::string& line) {
	std::vector<std::string> args = splitArguments(line);
	std::string cmd = args[0];

	if (currentUser && (cmd == "login" || cmd == "register")) {
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
	if (!currentUser) {
		std::println("[Error] You are not logged in!");
		return;
	}

	if (cmd == "help") { currentUser->help(); return; }
	if (cmd == "view-profile") { currentUser->viewProfile(); return; }

	auto visitor = CommandFactory::create(line);
	if (!visitor) {
		std::println("[Error] Unknown command!");
		return;
	}
	currentUser->accept(*visitor);
}

void Engine::proccessLogoutCommand(std::vector<std::string> args) {
	if (args.size() != 1) {
		std::println("[System] Unrecognized command");
		return;
	}
	if (!currentUser) {
		std::println("[System] You are already logged out!");
	}
	else {
		currentUser->logout();
		currentUser = nullptr;
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
