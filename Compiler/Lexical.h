#pragma once
#include "WordHashing.h"

class Lexical
{
private:
	char ch;
	std::string token_str;
	char id[10];
	std::fstream fs;
public:
	unsigned short sym;
	Lexical(std::string l_doc);
	int getsym();
	int getch();
};
