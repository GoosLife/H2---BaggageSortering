#pragma once
#include "TextGameObject.h"
#include "Terminal.h"

class TerminalGameObject : public TextGameObject
{
public:
	TerminalGameObject(const LoaderParams* pParams, Terminal* terminal);
	
	void draw();
	void update();
	void clean();

private:
	Terminal* terminal;
};