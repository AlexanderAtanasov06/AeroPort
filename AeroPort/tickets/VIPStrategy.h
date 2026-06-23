#pragma once
#include "IPricingStrategy.h"

class VIPStrategy : public IPricingStrategy {
public:
    double calculatePrice(double basePrice) const override;
    double getRefundAmount(double paidPrice) const override;
    bool isRefundable() const override;
    double getFreeBaggage() const override;

    std::string getName() const override;
};
