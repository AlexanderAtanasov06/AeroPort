#pragma once

class IPricingStrategy {
public:
    virtual double calculatePrice(double basePrice) const = 0;
    virtual double getRefundAmount(double paidPrice) const = 0;
    virtual bool isRefundable() const = 0;
    virtual double getFreeBaggage() const = 0;
    virtual ~IPricingStrategy() = default;
};
