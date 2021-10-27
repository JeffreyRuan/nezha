#pragma once
#include "Error.h"
#include "PrintHandler.h"

class PositionScan
{
private:
	Error errorMangager;
public:
	PositionScan();
	unsigned int line;
	unsigned int prevcharacter;
	unsigned int character;
	void reportError();
};
