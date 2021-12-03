#include "stdafx.h"
#include "PositionScan.h"

Error PositionScan::errorMangager;

PositionScan::PositionScan()
{
}

unsigned int PositionScan::line = 1;

unsigned int PositionScan::prevcharacter = 0;

unsigned int PositionScan::character = 0;

void PositionScan::reportError(const unsigned int& errortype, const std::string& store /*= ""*/)
{
	std::string WarningContext = warningVariant(errortype, store);

	PrintHandler::printError(line, character, prevcharacter, ++errorMangager.error, WarningContext);
}

void PositionScan::reportError(const unsigned int& errortype, unsigned int line, unsigned int prevcharacter, unsigned int character, const std::string& store /*= ""*/)
{
	std::string WarningContext = warningVariant(errortype, store);

	PrintHandler::printError(line, character, prevcharacter, ++errorMangager.error, WarningContext);
}

std::string PositionScan::warningVariant(const int& errortype, const std::string& store)
{
	std::string WarningContext;

	switch (errortype)
	{
	case 0: WarningContext = ""; break;
	case 1: WarningContext = format("\"{}\" is not an identifier", store); break;
	case 2: WarningContext = "missing closing quote"; break;
	case 3: WarningContext = "comment unclosed at end of file"; break;
	case 4: WarningContext = "unrecognized token"; break;
	case 5: WarningContext = "syntax error"; break;
	case 6: WarningContext = "semantic error"; break;
	case 7: WarningContext = "undeclared identifier"; break;
	case 8: WarningContext = "identifier has not been defined yet"; break;
	case 9: WarningContext = "there's illegal type"; break;
	case 10:WarningContext = "redeclared identifier"; break;
	default: WarningContext = ""; break;
	}

	return WarningContext;
}