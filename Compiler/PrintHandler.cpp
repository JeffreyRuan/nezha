#include "stdafx.h"
#include "PrintHandler.h"

using namespace std;

void PrintHandler::printError(unsigned int line, unsigned int character, unsigned int prevcharacter, unsigned int error_time, std::string WarningContext)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	if (character == 0)
	{
		cout << format("line: {}, character: {}; {}", line - 1, prevcharacter + 1, WarningContext) << endl << endl;
	}
	else
	{
		cout << format("line: {}, character: {}; {}", line, character, WarningContext) << endl << endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void PrintHandler::printLexicalDoublet(const std::string& word, const std::pair<int, int>& send)
{
#if DOUBLET_ONLY_NUM
	cout << format("lexing... < {}, {} >\n", send.first, send.second) << endl;
#else
	cout << format("lexing... < {}, {} >\n", word, send.first) << endl;
#endif
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

void PrintHandler::printParsingSuccessful()
{
	cout << endl << "Parsing completed and successful" << endl;
}

void PrintHandler::printParsingAction(const std::string& token, const TraceElem& e, const std::string& action)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6);
	cout << format("Token: {}, Top: {} <{},{}> {}, ACTION: {}\n", token, e.status, e.doublet.first, e.doublet.second, e.label, action);
	SetConsoleTextAttribute(hConsole, 7);
}