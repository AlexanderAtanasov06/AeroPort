#pragma once
#include "CommandFactory.h"
#include "User.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include <string>
#include <memory>
#include <vector>
#include <print>
#include <sstream>

class Engine {
public:
	Engine();
	bool isRunning;
	std::shared_ptr<User> currentUser;
	std::shared_ptr<AirportAuthority> admin;
	//std::vector<std::shared_ptr<Passenger>> passengers;
	//std::vector<std::shared_ptr<Dispatcher>> dispatchers;
	std::vector<std::shared_ptr<User>> users;

	static Engine& getInstance();
	void processCommand(const std::string& line);
	//void proccessRegisterCommand(std::vector<std::string> args);
	//void proccessLoginCommand(std::vector<std::string> args);
	//void proccessLogoutCommand(std::vector<std::string> args);
	std::vector<std::string> splitArguments(const std::string& line);
	void run();
};
