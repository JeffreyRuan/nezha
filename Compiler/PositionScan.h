#pragma once
#include "Error.h"
#include "PrintHandler.h"

class PositionScan
{
private:
	Error errorMangager;
public:
	PositionScan();
	static unsigned int line;
	static unsigned int prevcharacter;
	static unsigned int character;
	void reportError(const unsigned int& errortype, const std::string& store = "");
};
