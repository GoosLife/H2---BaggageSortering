#include "TerminalGameObject.h"

TerminalGameObject::TerminalGameObject(const LoaderParams* pParams, Terminal* terminal) : TextGameObject(pParams)
{
	this->terminal = terminal;
	update();
}

void TerminalGameObject::draw() { TextGameObject::draw(); }

void TerminalGameObject::update() {
	std::stringstream ss;
	ss << "Terminal " << terminal->GetID() + 1 << " - " << terminal->GetBaggageCount() << "/" << Terminal::GetMaxBaggage() << " baggage";

	text = ss.str();
}

void TerminalGameObject::clean()
{ 
	TextGameObject::clean(); 
}