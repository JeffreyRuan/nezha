#pragma once
#include "Error.h"
class PositionScan
{
private:
	Error errorMangager;
public:
	PositionScan();
	unsigned int line;
	unsigned int character;
	void reportError();
};
