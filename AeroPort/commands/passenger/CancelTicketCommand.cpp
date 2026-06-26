#include "CancelTicketCommand.h"

CancelTicketCommand::CancelTicketCommand(const std::string& flightId)
    : flightId(flightId) {
    if (flightId.empty()) {
        throw std::invalid_argument("[Error] Flight ID cannot be empty!");
    }
}

void CancelTicketCommand::visit(Passenger& p) {
    Engine& e = Engine::getInstance();
    std::shared_ptr<Flight> flight = nullptr;

    for (const auto& airline : e.getAirlines()) {
        flight = airline->findFlight(flightId);
        if (flight) {
            break;
        }
    }

    if (!flight) {
        std::println("[Error] Flight {} does not exist!", flightId);
        return;
    }

    std::vector<std::shared_ptr<Ticket>> candidates;
    for (const auto& ticket : p.getTickets()) {
        if (ticket->getFlightID() == flightId) {
            candidates.push_back(ticket);
        }
    }

    if (candidates.empty()) {
        std::println("[Error] You don't have any tickets for flight {}!", flightId);
        return;
    }

    if (candidates.size() > 1) {
        std::println("[System] Multiple tickets found for {}. Auto-selecting the highest class refundable ticket...", flightId);
    }

    std::shared_ptr<Ticket> bestTicket = nullptr;
    for (const auto& ticket : candidates) {
        if (ticket->isRefundable()) {
            if (!bestTicket || ticket->getPrice() > bestTicket->getPrice()) {
                bestTicket = ticket;
            }
        }
    }

    if (!bestTicket) {
        std::println("[Error] Your remaining ticket for {} is 'LastMinute' type, which is non-refundable!", flightId);
        return;
    }

    double refundAmount = bestTicket->getRefundAmount();
    p.addFunds(refundAmount);

    std::string ticketTypeStr = bestTicket->getTicketTypeStr();

    p.removeTicket(bestTicket);
    flight->removeTicket(bestTicket);

    std::println("[Success] {} ticket for {} cancelled. Refunded: {:.2f} EUR. Current balance: {:.2f} EUR.",
        ticketTypeStr, flightId, refundAmount, p.getBalance());
}