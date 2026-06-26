#include "AirportReportCommand.h"
#include "Engine.h"
#include <print>

void AirportReportCommand::visit(AirportAuthority& a) {
    Engine& e = Engine::getInstance();

    double passengerTaxes = 0.0;
    double cargoTaxes = 0.0;
    double privateTaxes = 0.0;

    for (const auto& airline : e.getAirlines()) {
        for (const auto& flight : airline->getFlights()) {
            if (flight->getStatus() == Flight::Status::DEPARTED) {
                auto airplane = flight->getAirplane().lock();
                if (!airplane) continue;

                std::string type = airplane->getType();
                if (type == "PassengerPlane") {
                    double ticketRevenue = 0.0;
                    for (const auto& ticket : flight->getSoldTickets()) {
                        ticketRevenue += ticket->getPrice();
                    }
                    passengerTaxes += 0.10 * ticketRevenue;
                }
                else if (type == "CargoPlane") {
                    cargoTaxes += airplane->getCapacity() * 15.0;
                }
                else if (type == "PrivateJet") {
                    privateTaxes += 5000.0;
                }
            }
        }
    }

    double totalRevenue = passengerTaxes + cargoTaxes + privateTaxes;

    std::println("=== Global Airport Financial Report ===");
    std::println("Taxes from Passenger Flights: {:.2f} EUR", passengerTaxes);
    std::println("Taxes from Cargo Flights: {:.2f} EUR", cargoTaxes);
    std::println("Taxes from Private Flights: {:.2f} EUR", privateTaxes);
    std::println("Total Airport Revenue Generated: {:.2f} EUR", totalRevenue);
}