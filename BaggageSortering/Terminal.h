#pragma once
#include "Flight.h"

class Terminal
{
public:
	Terminal(int id) : id(id) {}
	~Terminal() {}

	void Run(); // Run the terminal
	void AddBaggage(); // Add baggage to the terminal

	// Getters
	int GetID() const { return id; } // Get the ID of the terminal

private:
	Flight* flight;
	Baggage* baggage[Flight::MaxBaggage];
	
	int id;
	
	void LoadPlane(); // Takes all the baggage from the terminal and loads it onto the plane
	void GetNextFlight(); // Get the next flight from the flight list
};