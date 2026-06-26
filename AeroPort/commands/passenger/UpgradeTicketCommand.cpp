#include "UpgradeTicketCommand.h"


static int ticketRank(const std::string& type) {
	if (type == "LastMinute") return 0;
	if (type == "Standard")   return 1;
	if (type == "VIP")        return 2;
	return -1;
}

UpgradeTicketCommand::UpgradeTicketCommand(const std::string& flightId,
	const std::string& newTicketType)
	: flightId(flightId), newTicketType(newTicketType) {

	if (flightId.empty()) {
		throw std::invalid_argument("[Error] Flight ID cannot be empty!");
	}
	if (newTicketType != "Standard" &&
		newTicketType != "LastMinute" &&
		newTicketType != "VIP") {
		throw std::invalid_argument(
			"[Error] Invalid ticket type! Must be: Standard, LastMinute or VIP.");
	}
}

void UpgradeTicketCommand::visit(Passenger& p) {
	std::shared_ptr<Flight> flight = nullptr;
	Engine& e = Engine::getInstance();

	for (const auto& airline : e.getAirlines()) {
		flight = airline->findFlight(flightId);
		if (flight) break;
	}

	if (!flight) {
		std::println("[Error] Flight {} does not exist!", flightId);
		return;
	}

	if (flight->getStatus() != Flight::Status::SCHEDULED &&
		flight->getStatus() != Flight::Status::DELAYED) {
		std::println("[Error] Flight {} is not available for upgrades (Status: {})!",
			flightId, flight->getStatusStr());
		return;
	}

	std::vector<std::shared_ptr<Ticket>> candidates;
	for (const auto& t : p.getTickets()) {
		if (t->getFlightID() == flightId && t->getTicketTypeStr() != "LastMinute") {
			candidates.push_back(t);
		}
	}

	if (candidates.empty()) {
		std::println("[Error] You do not have any tickets for flight {}!", flightId);
		return;
	}

	std::shared_ptr<Ticket> ticket = *std::min_element(
		candidates.begin(), candidates.end(),
		[](const auto& a, const auto& b) {
			return ticketRank(a->getTicketTypeStr()) < ticketRank(b->getTicketTypeStr());
		}
	);

	const std::string currentType = ticket->getTicketTypeStr();

	if (currentType == newTicketType) {
		std::println("[Error] Your {} ticket for flight {} is already {}!",
			currentType, flightId, newTicketType);
		return;
	}

	if (ticketRank(newTicketType) <= ticketRank(currentType)) {
		std::println("[Error] Cannot downgrade ticket from {} to {}! Upgrades only.",
			currentType, newTicketType);
		return;
	}

	if (flight->getAirplane().lock()->getType() == "CargoPlane" &&
		newTicketType == "VIP") {
		std::println("[Error] You cannot upgrade to VIP tickets for Cargo flights!");
		return;
	}

	double basePrice = flight->getBaseTicketPrice();
	double oldPrice = ticket->getPrice();

	std::unique_ptr<IPricingStrategy> newStrategy = TicketFactory::createStrategy(newTicketType);
	double newPrice = newStrategy->calculatePrice(basePrice);
	double priceDiff = newPrice - oldPrice;

	if (p.getBalance() < priceDiff) {
		std::println("[Error] Insufficient funds! Your balance: {:.2f} EUR. "
			"Required upgrade fee: {:.2f} EUR.",
			p.getBalance(), priceDiff);
		return;
	}

	p.deductFunds(priceDiff);
	ticket->upgradeStrategy(std::move(newStrategy), basePrice);

	std::println("[Success] {} ticket upgraded to {}. "
		"{}Paid difference: {:.2f} EUR. Current balance: {:.2f} EUR.",
		currentType,
		newTicketType,
		(newTicketType == "VIP" ? "+20kg free baggage. " : ""),
		priceDiff,
		p.getBalance());
}