#include "Engine.h"
#include <iostream>
#include <print>

Engine::Engine() : isRunning(true), currentUser(nullptr) {
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
	auto visitor = CommandFactory::create(line);
	if (!visitor) {
		std::println("[Error] Unknown command!");
		return;
	}
	if (!currentUser) {
		std::println("[Error] You are not logged in!");
		return;
	}
	currentUser->accept(*visitor);
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
