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
	BaggageSplitter();
	~BaggageSplitter();
	void Run(); // Run the baggage splitter
	void SortBaggage(Baggage baggage); // Sort the baggage into the correct flights

private:
	CheckInDesk* checkInDesks[Airport::NumberOfCheckInDesks];
	Terminal* terminals[Airport::NumberOfTerminals];
};

