#pragma once
#include "WordHashing.h"
#include "PositionScan.h"

class Lexical
{
private:
	char ch;
	char give_back;
	std::string store_str;
	std::string send;
	std::fstream fs;
	PositionScan pos_scanner;
	bool residue;
public:
	Symbol sym;
	Lexical(std::string l_doc);
	~Lexical();
	bool isChar(const char& ch);
	bool isNum(const char& ch);
	Symbol isKey(std::string store_str);
	int getsym();
	int getch();
};
