#include "StandardTicket.h"

double StandardTicket::getRefundAmount() {
    return paidAmount;
}

bool StandardTicket::isRefundable() {
    return true;
}
