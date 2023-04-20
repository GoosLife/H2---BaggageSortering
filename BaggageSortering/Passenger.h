#pragma once
#include <atomic>
#include "Baggage.h"

class Passenger
{
public:
	Passenger();
	// Passenger(int id, Baggage baggage, int destination) : passengerID(id), passengerBaggage(baggage), passengerDestination(destination) {}
	~Passenger() {}

	// Getters
	int GetPassengerID() const { return passengerID; } // Get the ID of the passenger
	Baggage GetPassengerBaggage() const { return passengerBaggage; } // Get the ID of the baggage of the passenger
private:
	int passengerID;
	Baggage passengerBaggage;
	int passengerDestination;
};

// Stores the ID of the latest passenger, so that the next passenger can get a unique ID
static inline std::atomic<int> latestPassengerId = 0;