#pragma once
#include "Baggage.h"
#include <atomic>

class Flight
{
	public:
	Flight();
	Flight(int id, int destination) : flightID(id), flightDestination(destination) {}
	~Flight() {}
	// Getters
	int GetFlightID() const { return flightID; } // Get the ID of the flight
	int GetFlightDestination() const { return flightDestination; } // Get the destination of the flight

private:
	int flightID;
	int flightDestination;
	Baggage* baggage; // Array of baggage loaded on the flight
};

static inline std::atomic<int> latestFlightId = 0; // Ensures that the next flight gets a unique ID