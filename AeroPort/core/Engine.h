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
private:
	Engine();
	bool isRunning;
	std::shared_ptr<User> currentUser;
	std::shared_ptr<AirportAuthority> admin;
	//std::vector<std::shared_ptr<Passenger>> passengers;
	//std::vector<std::shared_ptr<Dispatcher>> dispatchers;
	std::vector<std::shared_ptr<User>> users;
	std::vector<std::string> splitArguments(const std::string& line);
	void proccessLogoutCommand(std::vector<std::string> args);
	void proccessLoginCommand(std::vector<std::string> args);
	void proccessRegisterCommand(std::vector<std::string> args);
	void processCommand(const std::string& line);
	
public:
	static Engine& getInstance();
	void run();
};
