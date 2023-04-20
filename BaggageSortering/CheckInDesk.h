#pragma once
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "Baggage.h"

#define CHECKIN_MAX_QUEUE 60 // How many passengers can be in line to check in at any time

class CheckInDesk
{
public:
	CheckInDesk() {
		for (int i = 0; i < CHECKIN_MAX_QUEUE; i++) {
			baggage[i] = nullptr;
		}

		mtx = new std::mutex();
		cv = new std::condition_variable();
	}
	~CheckInDesk() {}
	
	void CheckInBaggage(Baggage baggage); // Add baggage to the baggage array
	Baggage RemoveBaggage(); // Send the baggage to the baggage sorting system

	bool IsFull() { return index >= CHECKIN_MAX_QUEUE; } // Check if the baggage array is full

	// Getters
	int GetBaggageCount() { return index; }
	std::mutex* GetMutex() { return mtx; }
	std::condition_variable* GetConditionVariable() { return cv; }

private:
	bool isFull = index >= CHECKIN_MAX_QUEUE;
	int index = 0; // Index of the next available spot in the baggage array
	Baggage* baggage[CHECKIN_MAX_QUEUE];
	std::mutex* mtx = nullptr;
	std::condition_variable* cv = nullptr;
};