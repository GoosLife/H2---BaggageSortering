#pragma once
#include "Flight.h"
#include "Baggage.h"

#include <mutex>
#include <condition_variable>

#define TERMINAL_MAX_BAGGAGE 150

class Terminal
{
public:
	Terminal(int id);
	~Terminal() {}

	void Run(); // Run the terminal
	void AddBaggage(Baggage* baggage); // Add baggage to the terminal
	Baggage* RemoveBaggage(); // Remove baggage from the terminal

	// Getters
	int GetID() const { return id; } // Get the ID of the terminal
	Flight* GetFlight() { return flight; }
	int GetBaggageCount() { return index; }
	static inline std::mutex* GetMutex() { return mtx; }
	static inline std::condition_variable* GetConditionVariable() { return cv; }

	// Setters
	void DecrementBaggageCount() { index--; }

private:
	Flight* flight;

	// Create array of baggage pointers of unknown size
	Baggage* baggage[TERMINAL_MAX_BAGGAGE];

	int id;
	int index = 0;
	
	void LoadPlane(); // Takes all the baggage from the terminal and loads it onto the plane
	void GetNextFlight(); // Get the next flight from the flight list

	static inline std::mutex* mtx = new std::mutex();
	static inline std::condition_variable* cv = new std::condition_variable();
};