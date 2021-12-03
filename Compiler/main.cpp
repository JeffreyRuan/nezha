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
		syntaxAnalyzer.processToken(lexicalAnalyzer, keep_push);
		if (lexover)
		{
			keep_push = false;
		}
	}
	PrintHandler::printIntermediates(Intermediate::InterM_q);

	system("pause");
}