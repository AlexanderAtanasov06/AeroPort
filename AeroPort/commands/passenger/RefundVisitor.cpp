#include "RefundVisitor.h"

RefundTicketVisitor::RefundTicketVisitor(const std::string& passengerName, const std::string& flightID)
	: passengerName(passengerName), flightID(flightID) {
}

void RefundTicketVisitor::visit(Passenger& p) {
	if (p.getName() == passengerName) {
		for (const auto& ticket : p.getTickets()) {
			if (flightID == ticket->getFlightID()) {
				p.addFunds(ticket->getPrice());
				std::println("[System] Auto-refunding {:.2f} EUR to passenger {}...", ticket->getPrice(), passengerName);
			}
		}
		p.removeTicketsWithFlightID(flightID);
	}
}

void RefundTicketVisitor::visit(AirportAuthority& a) {
}

void RefundTicketVisitor::visit(Dispatcher& a) {
}
