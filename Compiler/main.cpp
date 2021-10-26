#include "stdafx.h"
using namespace std;

int main(int argc, char* argv[])
{
	string doc_name = "No document connected.";

	switch (argc)
	{
	case 2: doc_name = argv[1]; break;
	default: break;
	}

	cout << doc_name << endl;
}