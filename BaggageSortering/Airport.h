#pragma once

#include "CheckInDesk.h"
#include "Terminal.h"

#include <vector>

/// <summary>
/// Stores information about the airport, specifically the number of check-in desks and terminals
/// </summary>
class Airport
{
public:
    static inline const int NumberOfCheckInDesks = 3;
    static inline const int NumberOfTerminals = 3;

    static inline const std::vector<CheckInDesk*> GetCheckInDesks() { return checkInDesks; }
    static inline const void AddCheckInDesk(CheckInDesk* checkInDesk) { checkInDesks.push_back(checkInDesk); }

    static inline const std::vector<Terminal*> GetTerminals() { return terminals; }
    static inline const void AddTerminal(Terminal* terminal) { terminals.push_back(terminal); }

private:
    static inline std::vector<CheckInDesk*> checkInDesks;
    static inline std::vector<Terminal*> terminals;
};