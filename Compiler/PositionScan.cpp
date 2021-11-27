#include "stdafx.h"
#include "PositionScan.h"

PositionScan::PositionScan()
{
}

unsigned int PositionScan::line = 1;

unsigned int PositionScan::prevcharacter = 0;

unsigned int PositionScan::character = 0;

void PositionScan::reportError(const unsigned int& errortype, const std::string& store)
{
	std::string WarningContext;
	switch (errortype)
	{
	case 0: WarningContext = ""; break;
	case 1: WarningContext = format("\"{}\" is not an identifier", store); break;
	case 2: WarningContext = "missing closing quote"; break;
	case 3: WarningContext = "comment unclosed at end of file"; break;
	case 4: WarningContext = "unrecognized token"; break;
	case 5: WarningContext = "unrecognized syntax"; break;
	default: WarningContext = ""; break;
	}
	PrintHandler::printError(line, character, prevcharacter, ++errorMangager.error, WarningContext);
}