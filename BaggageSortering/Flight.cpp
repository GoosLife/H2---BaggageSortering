#include "Flight.h"

Flight::Flight() {
	flightID = latestFlightId++;
	flightDestination = 0; // TODO: Generate a random destination from a list of currently available destinations
}