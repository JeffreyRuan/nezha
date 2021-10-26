#pragma once
#include "WordHashing.h"
#include "PositionScan.h"

class Lexical
{
private:
	char ch;
	std::string store_str;
	std::string send_str;
	std::fstream fs;
	std::pair<unsigned int, unsigned int> pos_ptr;
	PositionScan pos_scanner;
public:
	Symbol sym;
	Lexical(std::string l_doc);
	int getsym();
	int getch();
};
