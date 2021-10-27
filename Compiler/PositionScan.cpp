#include "stdafx.h"
#include "PositionScan.h"

PositionScan::PositionScan() :line(1), character(0)
{
}

void PositionScan::reportError()
{
	PrintHandler::printError(line, character, ++errorMangager.error);
}