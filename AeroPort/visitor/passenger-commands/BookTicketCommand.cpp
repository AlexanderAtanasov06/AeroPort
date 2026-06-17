#include "BookTicketCommand.h"
#include "TicketFactory.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"

BookTicketCommand::BookTicketCommand(const std::string& flightId, const std::string& ticketType)
    : flightId(flightId), ticketType(ticketType) {

    if (flightId.empty()) {
        throw std::invalid_argument("[Error] Flight ID cannot be empty!");
    }
    if (ticketType != "Standard" && ticketType != "LastMinute" && ticketType != "VIP") {
        throw std::invalid_argument("[Error] Invalid ticket type! Must be: Standard, LastMinute or VIP.");
    }
}

void BookTicketCommand::visit(Passenger& p) {
    std::shared_ptr<Flight> flight;
    Engine& e = Engine::getInstance();
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

    if (flight->getStatus() != Flight::Status::SCHEDULED &&
        flight->getStatus() != Flight::Status::DELAYED) {
        std::println("[Error] Flight {} is not available for booking (Status: {})!", 
                     flightId, flight->getStatusStr());
        return;
    }

    if (flight->getAirplane()->getType() == "CargoPlane" && ticketType == "VIP") {
        std::println("[Error] You cannot purchase VIP tickets for Cargo flights!");
        return;
    }

    if (!flight->hasAvailableSeats()) {
        std::println("[Error] Flight {} is fully booked!", flightId);
        return;
    }

    double basePrice = flight->getBaseTicketPrice();
    auto ticket = TicketFactory::createTicket(ticketType, p.getName(), flightId, basePrice);

    if (!ticket) {
        std::println("[Error] Could not create ticket of type {}!", ticketType);
        return;
    }

    double ticketPrice = ticket->getPrice();

    if (p.getBalance() < ticketPrice) {
        std::println("[Error] Insufficient funds! Your balance: {:.2f} EUR. Ticket price: {:.2f} EUR.",
                     p.getBalance(), ticketPrice);
        return;
    }

    p.deductFunds(ticketPrice);
    flight->addTicket(std::move(ticket));

    std::print("[Success] ");
    if (ticketType == "Standard") {
        std::print("Standard ");
    } else if (ticketType == "LastMinute") {
        std::print("LastMinute ");
    } else if (ticketType == "VIP") {
        std::print("VIP ");
    }
    std::println("ticket booked for {}. Paid: {:.2f} EUR. Current balance: {:.2f} EUR.",
        flightId, ticketPrice, p.getBalance());
}

void BookTicketCommand::visit(Dispatcher& d) {
    std::println("[Error] This command is not available for Dispatcher!");
}

void BookTicketCommand::visit(AirportAuthority& a) {
    std::println("[Error] This command is not available for System Administrator!");
}
