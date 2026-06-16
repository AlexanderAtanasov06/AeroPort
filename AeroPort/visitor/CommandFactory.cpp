#include "CommandFactory.h"

std::unique_ptr<CommandVisitor> CommandFactory::create(const std::string& line) {
	std::istringstream iss(line);
	std::string type;
	iss >> type;

	if (type == "add-funds") {
		double funds;
		iss >> funds;
		return std::make_unique<AddFundsCommand>(funds);
	}
	

	return nullptr;
}

std::vector<std::string> CommandFactory::splitArguments(const std::string& line) {
	std::vector<std::string> v;
	std::istringstream iss(line);
	std::string word;
	while (iss >> word) {
		v.push_back(word);
	}
	return v;
}
