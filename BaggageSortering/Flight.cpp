#include "Flight.h"
#include "Timer.h"

Flight::Flight() {
	flightID = latestFlightId++;
	flightDestination = "Nepal"; // TODO: Generate a random destination from a list of currently available destinations
	maxBaggage = rand() % 150 + 30; // The maximum amount of baggage that can be loaded on the flight

	int timeToDeparture = rand() % 150 + 50;
	flightTime = Timer::GetGlobalTime() + timeToDeparture;

	std::chrono::time_point currTime = std::chrono::system_clock::now();
	std::time_t currTimeT = std::chrono::system_clock::to_time_t(currTime);
	std::time_t departureTime = currTimeT + timeToDeparture;
	// std::chrono::seconds(timeToDeparture);
}

void Flight::LoadBaggage(Baggage* baggageToLoad)
{
	baggage[baggageCount] = baggageToLoad;
	baggageCount++;
}
