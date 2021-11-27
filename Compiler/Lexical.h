#pragma once
#include "WordHashing.h"
#include "PositionScan.h"

class Lexical
{
private:
	char ch;
	char give_back;
	std::string store_str;
	std::fstream fs;
	PositionScan pos_scanner;
	bool residue;
	static unsigned int store_cnt;
public:
	Symbol sym;
	std::pair<int, int> send;
	Lexical(std::string l_doc);
	~Lexical();
	bool isChar(const char& ch);
	bool isNum(const char& ch);
	Symbol isKey(std::string store_str);
	int getsym();
	int getch();
};
