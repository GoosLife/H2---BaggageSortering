#include "CheckInDesk.h"
#include "Baggage.h"

CheckInDesk::CheckInDesk(int id) : id(id)
{
	for (int i = 0; i < CHECKIN_MAX_QUEUE; i++)
	{
		baggage[i] = nullptr;
	}

	isFull = index >= CHECKIN_MAX_QUEUE;
}

CheckInDesk::~CheckInDesk()
{
	delete(mtx);
	delete(cv);
}

void CheckInDesk::CheckInBaggage(Baggage* b) {
	baggage[index] = b;
	index++;
	isFull = index >= CHECKIN_MAX_QUEUE;
}

// Remove baggage from the array
Baggage* CheckInDesk::RemoveBaggage() {
	Baggage* b = baggage[0];
	for (int i = 0; i < index; i++) {
		baggage[i] = baggage[i + 1];
	}
	index--;
	return b;
}

void CheckInDesk::ToggleOpen()
{
	isOpen = !isOpen;
}
