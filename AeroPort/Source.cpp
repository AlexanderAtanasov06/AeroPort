#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include "LastMinuteTicket.h"
#include "VIPTicket.h"
#include "Passenger.h"
#include "TicketFactory.h"
#include "Engine.h"
#include <vector>
#include <print>

using std::unique_ptr;
using std::shared_ptr;
int main() {
	std::shared_ptr<Airplane> at = std::make_shared<PrivateJet>("F16");
	unique_ptr<Airplane> uniquePlane1 = std::make_unique<PassengerPlane>("Boeing", 100);
	unique_ptr<Airplane> cloned1 = uniquePlane1->clone();
	shared_ptr<Airplane> shared = std::move(uniquePlane1);

	std::vector<shared_ptr<Airplane>> v;
	v.push_back(std::move(cloned1));
	v.push_back(shared);

	std::vector<shared_ptr<Airplane>> v2;
	v2.push_back(shared);

	unique_ptr<Ticket> s = std::make_unique<VIPTicket>("Alex", "SOF-CRL", 50);

	Passenger p("Alex", "1234");
	p.addFunds(100);

	auto t1 = TicketFactory::createTicket("Standard", "Alex", "SOF - CRL", 50);
	auto t2 = TicketFactory::createTicket("VIP", "Alex", "SOF - CRL", 50);

	Engine& engine = Engine::getInstance();

	std::shared_ptr<User> sharedPassenger = std::make_shared<AirportAuthority>(AirportAuthority::getInstance());
	sharedPassenger->help();

}