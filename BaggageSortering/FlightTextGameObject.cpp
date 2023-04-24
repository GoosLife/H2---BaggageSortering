#include "FlightTextGameObject.h"

FlightTextGameObject::FlightTextGameObject(const LoaderParams* pParams, Terminal* terminal) : TerminalGameObject(pParams, terminal) { this->terminal = terminal; delete pParams; }

void FlightTextGameObject::draw()
{
	TextGameObject::draw();
}

void FlightTextGameObject::update()
{
	std::stringstream ss;
	ss << Timer::GetRealTimeString(terminal->GetFlight()->GetDepartureTimeT()) << ' ' << terminal->GetFlight()->GetDestination() << ' ' << terminal->GetFlight()->GetID() << ' ' << terminal->GetID() << ' ' << terminal->GetFlight()->GetBaggageCount() << '/' << terminal->GetFlight()->GetMaxBaggage();

	text = ss.str();
}

void FlightTextGameObject::clean()
{
	TerminalGameObject::clean();
}
