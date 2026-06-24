#include "UndoCommand.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include <print>

void UndoCommand::visit(Passenger& p) {
    std::println("[Error] This command is not available for Passenger!");
}

void UndoCommand::visit(AirportAuthority& a) {
    std::println("[Error] This command is not available for System Administrator!");
}

void UndoCommand::visit(Dispatcher& d) {
    d.undoLastAction();
}
