#pragma once
#include "Baggage.h"
#include <atomic>
#include <string>

#define MAX_BAGGAGE_PER_FLIGHT 150	// The maximum amount of baggage that can be loaded on a flight
									// Used for initializing the baggage array
									// The actual maximum amount of baggage that can be loaded on a flight is a random number between 30 and 180

struct Time {
	int hours;
	int minutes;
	int seconds;
};

class Flight
{
	public:
	Flight();
	~Flight() {}

	void LoadBaggage(Baggage* baggageToLoad);

	// Getters
	int GetID() const { return flightID; } // Get the ID of the flight
	std::string GetDestination() const { return flightDestination; } // Get the destination of the flight
	int GetMaxBaggage() const { return maxBaggage; } // Get the maximum amount of baggage that can be loaded on the flight
	int GetBaggageCount() { return baggageCount; }
	bool IsFull() { return baggageCount >= maxBaggage; } // Check if the flight is full

private:
	int flightID;
	std::string flightDestination;
	int maxBaggage; // The maximum amount of baggage that can be loaded on the flight
	Baggage* baggage[256]; // Array of baggage loaded on the flight (size is 256 but the actual size must not exceed the maxBaggage value)
	int baggageCount = 0;
};

static inline std::atomic<int> latestFlightId = 0; // Ensures that the next flight gets a unique ID