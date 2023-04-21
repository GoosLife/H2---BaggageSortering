#include "BaggageSplitter.h"
#include <iostream>

void BaggageSplitter::Run()
{
	std::unique_lock ul(*CheckInDesk::GetMutex(), std::defer_lock);

	BaggageSplitter* referenceToSelf = this;

	CheckInDesk::GetConditionVariable()->wait(ul, [&referenceToSelf]
		{
			// std::cout << "Baggagesplitter has the lock\n";
			// Check if there is any baggage to sort
			for (int i = 0; i < Airport::NumberOfCheckInDesks; i++)
			{
				if (referenceToSelf->GetCheckInDesk(i)->GetBaggageCount() > 0)
				{
					int amountOfBaggage = referenceToSelf->GetCheckInDesk(i)->GetBaggageCount();

					// std::cout << "There was " << amountOfBaggage << " baggage to sort\n";

					for (int j = 0; j < amountOfBaggage; j++)
					{
						Baggage baggage = referenceToSelf->GetCheckInDesk(i)->RemoveBaggage();
						referenceToSelf->SortBaggage(baggage);
					}
				}
			}

			// std::cout << "Baggagesplitter is releasing the lock\n";
			return true;
		});
	CheckInDesk::GetConditionVariable()->notify_one();

	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void BaggageSplitter::SortBaggage(Baggage baggage)
{

}