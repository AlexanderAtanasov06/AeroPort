#include "Dispatcher.h"

Dispatcher::Dispatcher(const std::string& name, const std::string& pass)
	: User(name, pass, User::Role::AIR_TRAFFIC_CONTROL) {
}
