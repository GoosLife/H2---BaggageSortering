#pragma once
#include <atomic>

static inline std::atomic<int> latestBaggageId = 0; // Ensures that the next baggage gets a unique ID

class Baggage
{
public:
	Baggage();
	~Baggage() {}
	// Getters
	int GetID() const { return id; } // Get the ID of the baggage
	int GetDestinationTerminal() const { return destinationTerminal; } // Get the destination of the baggage

	// Setters
	void SetDestinationTerminal(int destinationTerminal) { this->destinationTerminal = destinationTerminal; } // Set the destination of the baggage (for testing purposes)

private:
	int id;
	int destinationTerminal;
};