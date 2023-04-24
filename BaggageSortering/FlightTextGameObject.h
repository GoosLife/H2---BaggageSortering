#pragma once
#include "TerminalGameObject.h"
#include "Terminal.h"
#include "Flight.h"

class FlightTextGameObject : public TerminalGameObject
{
public:
	FlightTextGameObject(const LoaderParams* pParams, Terminal* terminal);	// All flights are bound to a terminal, 
																			// so it makes sense to have a reference to the terminal, 
																			// then use that to get all the flights,
																			// instead of having a reference to all the flights
																			// and then creating a new object for each flight.
																			// This way, the GUI only needs to add an object for each terminal.
	void draw();
	void update();
	void clean();

private:
	Terminal* terminal;
};