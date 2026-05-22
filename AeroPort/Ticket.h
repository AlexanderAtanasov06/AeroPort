#pragma once
#include <string>

class Ticket {
public:
	enum class TicketType {
		STANDART,
		LAST_MINUTE,
		VIP
	};
protected:
	std::string passengerName;
	std::string flightID;
	TicketType ticketType;
	double paidAmount;
	double baggageWeight;
public:
	Ticket(const std::string& name, const std::string& flightID, TicketType type, double amount, double baggage);
	virtual ~Ticket() = default;

	virtual double getRefundAmount() = 0;
	virtual bool isRefundable() = 0;

	//virtual void addBaggage(double weight);

	std::string getPassengerName() const;
	std::string getFlightId() const;
	double getPaidAmount() const;
	double getBaggageWeight() const;
	TicketType getType() const;
};