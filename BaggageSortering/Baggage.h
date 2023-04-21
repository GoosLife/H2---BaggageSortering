#pragma once
#include <atomic>

static inline std::atomic<int> latestBaggageId = 0; // Ensures that the next baggage gets a unique ID

class Baggage
{
public:
	Baggage() { id = latestBaggageId++; destination = 0; }
	~Baggage() {}
	// Getters
	int GetID() const { return id; } // Get the ID of the baggage
	int GetDestination() const { return destination; } // Get the destination of the baggage

private:
	int id;
	int destination;
};