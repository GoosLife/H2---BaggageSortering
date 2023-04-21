#include "Flight.h"

Flight::Flight() {
	flightID = latestFlightId++;
	flightDestination = "Nepal"; // TODO: Generate a random destination from a list of currently available destinations
	maxBaggage = rand() % 150 + 30; // The maximum amount of baggage that can be loaded on the flight
}

void Flight::LoadBaggage(Baggage* baggageToLoad)
{
	baggage[baggageCount] = baggageToLoad;
	baggageCount++;
}
