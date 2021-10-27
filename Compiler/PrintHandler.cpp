#include "stdafx.h"
#include "PrintHandler.h"

using namespace std;

void PrintHandler::printError(unsigned int line, unsigned int character, unsigned int error_time)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	cout << format("line: {}, character: {}; error({}).", line, character, error_time) << endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void PrintHandler::printLexicalDoublet(const std::string& word, const Symbol& sym)
{
	cout << format("< {}, {} >", word, static_cast<unsigned int>(sym)) << endl;
}