#include "stdafx.h"
#include "Parsing.h"
using namespace std;

int main(int argc, char* argv[])
{
	string doc_name;
	fstream t_fs;

#if ARG_REQUIRED
	if (PrintHandler::printCmdResp(argc, doc_name, argv, t_fs) != 0) return 0;
#else
	doc_name = "Code.txt";
#endif

	Lexical lexicalAnalyzer(doc_name);
	Parsing syntaxAnalyzer;
	int syntaxError = 0;
	bool lexover = false;
	bool keep_push = true;

	while (!lexover || !syntaxAnalyzer.buffer.empty())
	{
		if (!lexover)
		{
			if (lexicalAnalyzer.getsym() == 1)
			{
				lexover = true;
			}
		}
		syntaxError = syntaxAnalyzer.processToken(lexicalAnalyzer, keep_push);
		if (syntaxError == -1)
		{
			break;
		}
		if (lexover)
		{
			keep_push = false;
		}
	}

	if (syntaxError != -1)
	{
		//Add Program Name FTuple
		FTuple t_ftpl = { "program", Intermediate::programName, "-", "-" };
		Intermediate::InterM_q.insert(Intermediate::InterM_q.begin(), std::pair<FTuple, int>(t_ftpl, 0));
#if PRINT_INTERMEDIATE
		PrintHandler::printIntermediates(Intermediate::InterM_q);
#endif
	}

	system("pause");
}