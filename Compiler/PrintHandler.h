#pragma once
#include "WordHashing.h"

class PrintHandler
{
public:
	static void printError(unsigned int line, unsigned int character, unsigned int error_time);
	static void printLexicalDoublet(const std::string& word, const Symbol& sym);
};
