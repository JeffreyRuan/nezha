#pragma once
#include "WordHashing.h"
#include "LexStore.h"
#include "TraceElem.h"
#include "FTuple.h"

class PrintHandler
{
public:
	static void printError(unsigned int line, unsigned int character, unsigned int prevcharacter, unsigned int error_time, std::string WarningContext);
	static void printLexicalDoublet(const std::string& word, const std::pair<int, int>& send);
	static int printCmdResp(const int& argc, std::string& doc_name, char**& argv, std::fstream& t_fs);
	static void printParsingSuccessful();
	static void printParsingAction(const std::string& token, const TraceElem& e, const std::string& action);
	static void printIntermediates(std::vector<std::pair<FTuple, int>>& v);
};
