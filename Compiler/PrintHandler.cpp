#include "stdafx.h"
#include "PrintHandler.h"

using namespace std;

void PrintHandler::printError(unsigned int line, unsigned int character, unsigned int prevcharacter, unsigned int error_time)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	if (character == 0)
	{
		cout << format("line: {}, character: {}; error({}).", line - 1, prevcharacter + 1, error_time) << endl;
	}
	else
	{
		cout << format("line: {}, character: {}; error({}).", line, character, error_time) << endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void PrintHandler::printLexicalDoublet(const std::string& word, const Symbol& sym)
{
	cout << format("< {}, {} >", word, static_cast<unsigned int>(sym)) << endl;
}