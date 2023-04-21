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
		if (referenceToSelf->GetFlight()->IsFull()) {
			return true;
		}

		int startIndex = referenceToSelf->GetFlight()->GetBaggageCount();
		int maxValue = referenceToSelf->GetFlight()->GetMaxBaggage();

		int maxIterations = maxValue - startIndex;

		for (int i = 0; i < maxIterations; i++) {
			if (referenceToSelf->GetBaggageCount() > 0) {
				Baggage* baggageToLoad = referenceToSelf->RemoveBaggage();
				referenceToSelf->GetFlight()->LoadBaggage(baggageToLoad);
			}
			else {
				break; // No more baggage to load
			}
		}

		return true;});

	Terminal::GetConditionVariable()->notify_one();

	std::this_thread::sleep_for(std::chrono::seconds(2));
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
}
