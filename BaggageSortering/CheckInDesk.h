#pragma once
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "Baggage.h"

#define CHECKIN_MAX_QUEUE 60 // How many passengers can be in line to check in at any time

class CheckInDesk
{
public:
	CheckInDesk(int id);

	~CheckInDesk();
	
	void CheckInBaggage(Baggage* baggage); // Add baggage to the baggage array
	Baggage* RemoveBaggage(); // Send the baggage to the baggage sorting system

	void ToggleOpen(); // Toggle the open state of the check-in desk

	// Getters
	int GetBaggageCount() { return index; }
	int GetID() { return id; }

	bool IsFull() { return index >= CHECKIN_MAX_QUEUE; } // Check if the baggage array is full
	bool IsOpen() { return isOpen; } // Check if the check-in desk is open

	// Static getters
	static inline int GetMaxBaggage() { return CHECKIN_MAX_QUEUE; }
	static inline std::mutex* GetMutex() { return mtx; }
	static inline std::condition_variable* GetConditionVariable() { return cv; }

private:
	int id; // ID of the check-in desk
	int index = 0; // Index of the next available spot in the baggage array
	
	Baggage* baggage[CHECKIN_MAX_QUEUE]; // Baggage array
	
	bool isFull; // Is the baggage array full?
	bool isOpen = true; // Is the check-in desk open?
	
	static inline std::mutex* mtx = new std::mutex();
	static inline std::condition_variable* cv = new std::condition_variable();
};