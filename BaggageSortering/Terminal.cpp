#include "Terminal.h"

#include "Airport.h"

#include <mutex>
#include <condition_variable>

Terminal::Terminal(int id) : id(id) {
	flight = new Flight();
}

void Terminal::Run()
{
	std::unique_lock ul(*Terminal::GetMutex(), std::defer_lock);

	Terminal* referenceToSelf = this;

	Terminal::GetConditionVariable()->wait(ul, [&referenceToSelf] {

		// Escape if the flight is full
		if (!referenceToSelf->GetFlight()->IsFull())
		{
			if (referenceToSelf->GetBaggageCount() > 0)
			{
				Baggage* baggageToLoad = referenceToSelf->RemoveBaggage();
				referenceToSelf->GetFlight()->LoadBaggage(baggageToLoad);
			}
		}

		if (referenceToSelf->GetFlight()->IsDepartureTime())
		{
			referenceToSelf->GetFlight()->Depart();

			// Get the next flight
			referenceToSelf->GetNextFlight();
		}

		return true;});

	Terminal::GetConditionVariable()->notify_one();

	std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void Terminal::AddBaggage(Baggage* baggage) {
	this->baggage[index] = baggage;
	index++;
}

Baggage* Terminal::RemoveBaggage()
{
	Baggage* baggageToRemove = baggage[0];
	for (int i = 0; i < index; i++) {
		baggage[i] = baggage[i + 1];
	}
	index--;
	return baggageToRemove;
}

void Terminal::GetNextFlight()
{
	// Get the next flight from the flight list
	flight = new Flight(); // TODO: Get the next flight from the flight list instead of creating a new one. The flight list is a static variable in the Airport class that contains all the flights for the day
}
