#include "VIPTicket.h"

double VIPTicket::getRefundAmount() {
    return paidAmount;
}

bool VIPTicket::isRefundable() {
    return true;
}
