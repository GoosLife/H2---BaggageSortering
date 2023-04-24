#pragma once
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "Baggage.h"

#define CHECKIN_MAX_QUEUE 60 // How many passengers can be in line to check in at any time

class CheckInDesk
{
public:
	CheckInDesk(int id) : id(id) {
		for (int i = 0; i < CHECKIN_MAX_QUEUE; i++) {
			baggage[i] = nullptr;
		}

		isFull = index >= CHECKIN_MAX_QUEUE;
	}

	~CheckInDesk() {
		delete(mtx);
		delete(cv);
	}
	
	void CheckInBaggage(Baggage* baggage); // Add baggage to the baggage array
	Baggage* RemoveBaggage(); // Send the baggage to the baggage sorting system

	bool IsFull() { return index >= CHECKIN_MAX_QUEUE; } // Check if the baggage array is full

	// Getters
	int GetBaggageCount() { return index; }
	int GetID() { return id; }

	// Static getters
	static inline int GetMaxBaggage() { return CHECKIN_MAX_QUEUE; }
	static inline std::mutex* GetMutex() { return mtx; }
	static inline std::condition_variable* GetConditionVariable() { return cv; }

private:
	int id;
	bool isFull;
	int index = 0; // Index of the next available spot in the baggage array
	Baggage* baggage[CHECKIN_MAX_QUEUE];
	static inline std::mutex* mtx = new std::mutex();
	static inline std::condition_variable* cv = new std::condition_variable();
};