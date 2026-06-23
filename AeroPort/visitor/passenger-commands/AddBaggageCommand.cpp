#include "AddBaggageCommand.h"

AddBaggageCommand::AddBaggageCommand(const std::string& flightId, double weight)
    : flightId(flightId), weight(weight) {
    if (flightId.empty()) {
        throw std::invalid_argument("[Error] Flight ID cannot be empty!");
    }
    if (weight <= 0) {
        throw std::invalid_argument("[Error] Baggage weight must be a positive number!");
    }
}

void AddBaggageCommand::visit(Passenger& p) {
    std::vector<std::shared_ptr<Ticket>> matchingTickets;

    for (const auto& ticket : p.getTickets()) {
        if (ticket->getFlightID() == flightId) {
            matchingTickets.push_back(ticket);
        }
    }

    if (matchingTickets.empty()) {
        std::println("[Error] You don't have a booked ticket for flight {}!", flightId);
        return;
    }

    std::shared_ptr<Ticket> targetTicket = matchingTickets.front();

    if (matchingTickets.size() > 1) {
        constexpr double EPSILON = 1e-6;
        for (const auto& ticket : matchingTickets) {
            if (std::abs(ticket->calculateBaggageFee(1.0)) < EPSILON) {
                targetTicket = ticket;
                break;
            }
        }
        std::println("[System] Multiple tickets found for {}. Auto-selecting optimal ticket...", flightId);
    }

    double requiredAmount = targetTicket->calculateBaggageFee(weight);

    if (p.getBalance() < requiredAmount) {
        std::println("[Error] Insufficient funds! Your balance: {:.2f} EUR. Baggage fee: {:.2f} EUR.",
            p.getBalance(), requiredAmount);
        return;
    }

    p.deductFunds(requiredAmount);

    try {
        targetTicket->addBaggage(weight, requiredAmount);
        std::println("[Success] Added {} kg baggage to {} ticket. Fee: {:.2f} EUR. Current balance: {:.2f} EUR.",
            weight, flightId, requiredAmount, p.getBalance());
    }
    catch (const std::exception& e) {
        p.addFunds(requiredAmount);
        std::println("[Error] {}", e.what());
    }
}

void AddBaggageCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void AddBaggageCommand::visit(AirportAuthority& a) {
    std::println("[Error] This command is not available for System Administrator!");
}