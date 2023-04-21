#include "Baggage.h"

Baggage::Baggage()
{
	id = latestBaggageId;
	destinationTerminal = rand() % 3;
}
