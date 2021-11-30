#pragma once
#include "Error.h"
#include "PrintHandler.h"

class PositionScan
{
private:
	static Error errorMangager;
public:
	PositionScan();
	static unsigned int line;
	static unsigned int prevcharacter;
	static unsigned int character;
	static void reportError(const unsigned int& errortype, const std::string& store = "");
	static void reportError(const unsigned int& errortype, unsigned int line, unsigned int prevcharacter, unsigned int character, const std::string& store = "");
	static std::string warningVariant(const int& errortype, const std::string& store);
};
