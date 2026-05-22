#include "LastMinuteTicket.h"

LastMinuteTicket::LastMinuteTicket(const std::string& name, const std::string& flightID, double amount, double baggage) : Ticket(name, flightID, Ticket::TicketType::LAST_MINUTE, amount, baggage) {}

double LastMinuteTicket::getRefundAmount() {
    return 0;
}

bool LastMinuteTicket::isRefundable() {
    return false;
}
