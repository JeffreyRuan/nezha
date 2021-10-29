#pragma once
#include "WordHashing.h"
#include "Store.h"

class PrintHandler
{
private:
	static unsigned int store_cnt;
public:
	static void printError(unsigned int line, unsigned int character, unsigned int prevcharacter, unsigned int error_time, std::string WarningContext);
	static void printLexicalDoublet(const std::string& word, const Symbol& sym);
	static int printCmdResp(const int& argc, std::string& doc_name, char**& argv, std::fstream& t_fs);
};
