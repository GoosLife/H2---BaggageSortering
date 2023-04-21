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
	BaggageSplitter(CheckInDesk** checkInDesks, Terminal** terminals) {
		for (int i = 0; i < Airport::NumberOfCheckInDesks; i++)
		{
			this->checkInDesks[i] = checkInDesks[i];
		}

		for (int i = 0; i < Airport::NumberOfTerminals; i++)
		{
			this->terminals[i] = terminals[i];
		}
	}
	~BaggageSplitter() {}
	void Run(); // Run the baggage splitter
	void SortBaggage(Baggage* baggage); // Sort the baggage into the correct flights

	CheckInDesk* GetCheckInDesk(int index) { return checkInDesks[index]; }
	Terminal* GetTerminal(int index) { return terminals[index]; }

private:
	CheckInDesk* checkInDesks[Airport::NumberOfCheckInDesks];
	Terminal* terminals[Airport::NumberOfTerminals];
};

