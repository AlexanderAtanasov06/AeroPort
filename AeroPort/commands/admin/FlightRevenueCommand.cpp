#include "FlightRevenueCommand.h"
#include "Engine.h"
#include <print>

FlightRevenueCommand::FlightRevenueCommand(const std::string& flightID) : flightID(flightID) {
    if (flightID.empty()) {
        throw std::invalid_argument("[Error] Flight ID cannot be empty!");
    }
}

void FlightRevenueCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void FlightRevenueCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void FlightRevenueCommand::visit(AirportAuthority& a) {
    Engine& e = Engine::getInstance();

    std::shared_ptr<Flight> targetFlight = nullptr;
    for (const auto& airline : e.getAirlines()) {
        targetFlight = airline->findFlight(flightID);
        if (targetFlight) {
            break;
        }
    }

    if (!targetFlight) {
        std::println("[Error] Flight '{}' not found!", flightID);
        return;
    }

    auto airplane = targetFlight->getAirplane().lock();
    if (!airplane) {
        std::println("[Error] Flight '{}' has no valid airplane assigned!", flightID);
        return;
    }

    double ticketRevenue = 0.0;
    for (const auto& ticket : targetFlight->getSoldTickets()) {
        ticketRevenue += ticket->getPrice();
    }

    double airportTax = 0.0;
    std::string type = airplane->getType();

    if (type == "PassengerPlane") {
        airportTax = 0.10 * ticketRevenue;
    }
    else if (type == "CargoPlane") {
        airportTax = airplane->getCapacity() * 15.0;
    }
    else if (type == "PrivateJet") {
        airportTax = 5000.0;
    }

    double netProfit = ticketRevenue - airportTax;

    std::println("=== Flight Revenue Report: {} ===", flightID);
    std::println("Total Ticket Revenue: {:.2f} EUR", ticketRevenue);
    std::println("Airport Tax Deducted: {:.2f} EUR", airportTax);
    std::println("Net Profit for Airline: {:.2f} EUR", netProfit);
}