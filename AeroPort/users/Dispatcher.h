#pragma once
#include <string>
#include "User.h"

class Dispatcher : public User {
public:
	Dispatcher(const std::string& name, const std::string& pass);

	void help() const override;
};