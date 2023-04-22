#pragma once

#include "Airport.h"
#include "Flight.h"
#include "Timer.h"

/// <summary>
/// Keeps track of the flights and their departure times
/// </summary>
class FlightScheduler
{
public:
	FlightScheduler();
	~FlightScheduler() {}
	void Run(); // Run the flight scheduler
	void AddFlight(Flight* flight); // Add a flight to the flight list
	Flight* GetFlight(int index); // Get a flight from the flight list
	int GetFlightCount() { return flightCount; } // Get the number of flights in the flight list

private:
	Flight* flights[Airport::NumberOfTerminals];
	void RemoveFlight(int index); // Remove a flight from the flight list
	int flightCount = 0;
};