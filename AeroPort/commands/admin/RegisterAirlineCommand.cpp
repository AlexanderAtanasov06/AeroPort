#include "RegisterAirlineCommand.h"

RegisterAirlineCommand::RegisterAirlineCommand(const std::string& name, double balance)
    : name(name), balance(balance) {
    if (balance < 0 ) {
        throw std::invalid_argument("[Error] Initial balance must be a positive number!");
    }
}

void RegisterAirlineCommand::visit(AirportAuthority& a) {
    Engine& e = Engine::getInstance();

    auto it = e.findAirline(name);
    if (it) {
        std::println("[Error] An airline with this name already exists!");
        return;
    }

    auto airline = std::make_unique<Airline>(name, balance);
    e.addAirline(std::move(airline));
    std::println("[System] Airline '{}' registered successfully. Corporate Balance: {:.2f} EUR.", name, balance);
}