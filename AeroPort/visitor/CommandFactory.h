#pragma once
#include <memory>
#include <sstream>
#include <vector>
#include <print>
#include "CommandVisitor.h"
#include "AddFundsCommand.h"

class CommandFactory {
private:
	std::vector<std::string> splitArguments(const std::string& line);
public:
	CommandFactory() = delete;
	static std::unique_ptr<CommandVisitor> create(const std::string& line);
};