#pragma once
#include <string>

class Ticket {
private:
	static constexpr double BAGGAGE_FEE_PER_KILO_IN_EUR = 5;
public:
	enum class TicketType {
		STANDARD,
		LAST_MINUTE,
		VIP
	};
protected:
	std::string passengerName;
	std::string flightID;
	TicketType ticketType;
	double price;
	double baggageWeight;
	double remainingFreeBaggage;
public:
	Ticket(const std::string& passengerName, const std::string& flightID, TicketType type, double price, double remainingFreeBaggage);
	virtual ~Ticket() = default;

	virtual double getRefundAmount() = 0;
	virtual bool isRefundable() = 0;

	double calculateBaggageFee(double weight) const;
	void addBaggage(double weight, double paid);

	double getTicketPrice() const;
	std::string getPassengerName() const;
	std::string getFlightId() const;
	double getPrice() const;
	double getBaggageWeight() const;
	TicketType getType() const;
};