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

int PrintHandler::printCmdResp(const int& argc, string& doc_name, char**& argv, fstream& t_fs)
{
	switch (argc)
	{
	case 2: doc_name = argv[1];
		t_fs.open(doc_name);
		if (!t_fs.is_open()) {
			cout << format("\'{}\' is not a source file.", argv[1]) << endl; return 1;
		}
		t_fs.close();
		break;
	case 1: cout << "No source files connected." << endl; return 2; break;
	default:
		string sum;
		for (int i = 1; i < argc - 1; i++) { sum += argv[i]; sum += " "; } sum += argv[argc - 1];
		cout << format("\'{}\' is not a nezha command.", sum) << endl; return 3; break;
	}
	return 0;
}