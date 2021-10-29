#include "stdafx.h"
#include "Lexical.h"
using namespace std;
#define NAME_REQUIRED 1;

int main(int argc, char* argv[])
{
	string doc_name;
	fstream t_fs;

#if NAME_REQUIRED
	doc_name = "Code.txt";
	wstring classname, studentname, identity;
	//wcin >> classname >> studentname >> identity;
#else
	if (PrintHandler::printCmdResp(argc, doc_name, argv, t_fs) != 0) return 0;
#endif

	Lexical lexicalAnalyzer(doc_name);

	while (lexicalAnalyzer.getsym() != 1)
	{
	}
	system("pause");
}