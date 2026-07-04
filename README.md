# AeroPort — Airport Business Manager

A C++ console application developed as a course project for the Object-Oriented Programming (OOP) Practicum (2025-2026) at FMI, Sofia University. The system simulates an airport ecosystem, allowing airlines to manage fleets and schedule flights, dispatchers to coordinate runways, and passengers to book tickets.

---

## Main Design Patterns Used

The project relies on several key design patterns to enforce low coupling and clean architecture without using `dynamic_cast`:

1. **Singleton Pattern**: Ensures a single instance of the application core (`Engine`) and enforces a strict system-wide limit of exactly one System Administrator (`AirportAuthority`).
2. **Builder Pattern**: Implemented via `Runway::Builder` to modularly construct airport runways with various optional components (`ILS`, `VIP`, `HeavyDuty`).
3. **Strategy Pattern**: Decouples ticket types (`Standard`, `LastMinute`, `VIP`) from pricing logic through the `IPricingStrategy` interface, dynamically calculating fares, cancellation rules, and baggage policies.
4. **Observer Pattern**: Handles weather updates (`WeatherSubject`), where active flights register as `IWeatherObserver`s to automatically cancel and initiate mass refunds in case of a severe `STORM`.
5. **Visitor Pattern**: Utilized by `CommandVisitor` to map runtime text inputs to specific user execution flows (`Passenger`, `Dispatcher`, `AirportAuthority`) without relying on RTTI. Also used in `RefundTicketVisitor` for handling user data traversals.
6. **Factory Pattern**: Separates object creation from execution loops across three dedicated factories: `CommandFactory`, `TicketFactory`, and `AirplaneFactory`.
7. **Command Pattern with Undo**: Dispatcher flight traffic operations are encapsulated into executable objects. Last-performed dispatch actions are pushed into an undo stack to support seamless state reversal via `undo`.
8. **Prototype Pattern (Clone)**: Used in the airplane hierarchy through a pure virtual `clone()` method. This permits the system to produce precise runtime duplicates of an existing aircraft in an airline's fleet via `clone-aircraft`.

---

## Build System & Requirements

The project uses the following modern C++ build infrastructure:
* **Build Tool:** [CMake](https://cmake.org/) (Minimum version 3.20)
* **Build Generator:** [Ninja](https://ninja-build.org/)
* **Language Standard:** C++23 / C++ Latest (`/std:c++latest`)

---

## Command Reference

### Base & Authentication Commands
* `login <username> <password>` — Log into a session.
* `register <username> <password> <Passenger/Dispatcher>` — Register a standard user.
* `help` | `view-profile` | `logout` — Base session interactions.
* `save` | `load` — Serialize or deserialize the airport state.

### 1. System Administrator (`AirportAuthority`)
* `build-runway <id> <length> [ILS] [VIP] [HeavyDuty]` — Build an entry runway.
* `build-hangar <id> <capacity> <repair_fee>` — Build an aircraft service depot.
* `close-runway <runway_id>` — Set a runway status to maintenance.
* `set-weather <SUNNY/STORM>` — Trigger global climate shifts.
* `register-airline <name> <initial_capital>` — Instantiate a corporate airline entry.
* `buy-aircraft <airline> <PassengerPlane/CargoPlane/PrivateJet> <model> <cap>` — Purchase a vehicle.
* `clone-aircraft <id> <count>` — Create precise functional copies of an aircraft.
* `send-to-hangar <aircraft_id> <hangar_id>` | `retrieve-from-hangar <aircraft_id>` — Maintain fleet health.
* `schedule-flight <flight_id> <aircraft_id> <destination> <base_price>` — Plan a flight route.
* `cancel-flight <flight_id>` — Terminate a flight and trigger passenger refunds.
* `flight-revenue <flight_id>` | `airport-report` | `audit-airline <name>` — Financial audits.

### 2. Dispatcher (`Air Traffic Control`)
* `list-airspace` — View pending flights awaiting track access.
* `list-runways` — Review real-time lane occupancy.
* `assign-runway <flight_id> <runway_id>` — Route a flight to validation checks and boarding status.
* `delay-flight <flight_id>` — Postpone a flight schedule.
* `free-runway <runway_id>` — Clear a runway, triggering the flight departure, airline income payout, and component wear.
* `undo` — Revert the dispatcher's preceding traffic control operation.

### 3. Passenger (`Passenger`)
* `add-funds <amount>` — Deposit assets into user capital.
* `list-flights <destination>` | `filter-flights <max_price>` — Discover active lines.
* `book-ticket <flight_id> <Standard/LastMinute/VIP>` — Reserve a seat or space.
* `upgrade-ticket <flight_id> <new_type>` — Buy into a superior strategy tier.
* `add-baggage <flight_id> <weight>` — Pay surcharges for exceeding weight criteria.
* `cancel-ticket <flight_id>` — Relinquish a ticket reservation according to refund restrictions.
* `my-tickets` — Review all active reservations and corresponding destination states.
