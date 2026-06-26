#include "ListAirspaceCommand.h"
#include "Engine.h"
#include <print>

void ListAirspaceCommand::visit(Dispatcher& d) {
    Engine& e = Engine::getInstance();
    
    std::println("Pending Airspace Traffic (Scheduled / Delayed):");

    int count = 1;
    
    for (const auto& airline : e.getAirlines()) {
        for (const auto& flight : airline->getFlights()) {
            auto status = flight->getStatus();
            
            if (status == Flight::Status::SCHEDULED || status == Flight::Status::DELAYED) {
                auto airplane = flight->getAirplane().lock();
                if (airplane) {
                    std::println("{}. {} [{}] - {}", 
                        count++, 
                        flight->getFlightID(), 
                        airplane->getType(), 
                        flight->getDestination()
                    );
                }
            }
        }
    }

    if (count == 1) {
        std::println("[System] No pending flights in the airspace.");
    }
}