#include "stdafx.h"
#include "Lexical.h"
using namespace std;

int main(int argc, char* argv[])
{
	string doc_name = "Code.txt";

	/*switch (argc)
	{
	case 2: doc_name = argv[1]; break;
	default: cout << "No document connected." << endl ; return 1; break;
	}*/

	Lexical lexicalAnalyzer(doc_name);

	for (int i = 0; i < 500; i++)
	{
		lexicalAnalyzer.getsym();
	}
}