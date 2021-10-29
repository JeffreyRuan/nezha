#include "stdafx.h"
#include "Lexical.h"
using namespace std;

int main(int argc, char* argv[])
{
	string doc_name;
	fstream t_fs;

#if ARG_REQUIRED
	if (PrintHandler::printCmdResp(argc, doc_name, argv, t_fs) != 0) return 0;
#else
	doc_name = "Code.txt";
	wstring classname, studentname, identity;
	//wcin >> classname >> studentname >> identity;
#endif

	Lexical lexicalAnalyzer(doc_name);

	while (lexicalAnalyzer.getsym() != 1)
	{
	}
	system("pause");
}