#pragma once
#include "WordHashing.h"
#include "PositionScan.h"

class Lexical
{
private:
	char ch;
	bool unusedch;
	char give_back;
	std::string store_str;
	std::string send_str;
	std::fstream fs;
	std::pair<unsigned int, unsigned int> pos_ptr;
	PositionScan pos_scanner;
public:
	Symbol sym;
	Lexical(std::string l_doc);
	bool isChar(const char& ch);
	int getsym();
	int getch();
};
