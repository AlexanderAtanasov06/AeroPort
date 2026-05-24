#include "LastMinuteTicket.h"

LastMinuteTicket::LastMinuteTicket(const std::string& name, const std::string& flightID, double amount) : Ticket(name, flightID, Ticket::TicketType::LAST_MINUTE, amount) {}

double LastMinuteTicket::getRefundAmount() {
    return 0;
}

bool LastMinuteTicket::isRefundable() {
    return false;
}
