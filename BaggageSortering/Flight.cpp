#include "Flight.h"
#include "Timer.h"

Flight::Flight() {
	flightID = latestFlightId++;
	flightDestination = "Nepal"; // TODO: Generate a random destination from a list of currently available destinations
	maxBaggage = rand() % 150 + 30; // The maximum amount of baggage that can be loaded on the flight

	int timeToDeparture = rand() % 150 + 50;
	flightTime = Timer::GetGlobalTime() + timeToDeparture;

	std::chrono::system_clock::time_point currTime = std::chrono::system_clock::now();
	currTime += std::chrono::seconds(timeToDeparture);
	std::time_t departureTime = std::chrono::system_clock::to_time_t(currTime);
	// std::chrono::seconds(timeToDeparture);

	char s_now[26];
	ctime_s(s_now, sizeof(s_now), &departureTime);

	realTimeDeparture = s_now;
}

Flight::~Flight()
{
	//// Delete all the baggage that is loaded on the flight
	//for (int i = 0; i < baggageCount; i++)
	//{
	//	delete baggage[i];
	//}
	//
	//delete this;
}

void Flight::LoadBaggage(Baggage* baggageToLoad)
{
	baggage[baggageCount] = baggageToLoad;
	baggageCount++;
}

// This just calls the destructor, but it's more clear to call this function when a flight departs
void Flight::Depart()
{
	realTimeDeparture = "Departed";
	this->~Flight();
}