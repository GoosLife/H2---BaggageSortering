#pragma once
#include "Airport.h"
#include "Baggage.h"
#include "CheckInDesk.h"
#include "Terminal.h"

/// <summary>
/// Takes baggage from the check-in desks and splits it into the correct flights
/// </summary>
class BaggageSplitter
{
public:
	BaggageSplitter(CheckInDesk** checkInDesks, Terminal** terminals);
	~BaggageSplitter() {}
	void Run(); // Run the baggage splitter
	void SortBaggage(Baggage* baggage); // Sort the baggage into the correct terminals

	CheckInDesk* GetCheckInDesk(int index) { return checkInDesks[index]; }
	Terminal* GetTerminal(int index) { return terminals[index]; }

private:
	CheckInDesk* checkInDesks[Airport::NumberOfCheckInDesks];
	Terminal* terminals[Airport::NumberOfTerminals];
};

