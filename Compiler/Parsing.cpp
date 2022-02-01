#include "stdafx.h"
#include"Parsing.h"
using namespace std;

int Parsing::processToken(const Lexical& lobj, const bool& keep_push)
{
	if (keep_push && !(lobj.send.first == static_cast<int>(Symbol::comment) || lobj.send.first == static_cast<int>(Symbol::nul)))
	{
		buffer.push(TokenParam(lobj.send, lobj.currpos));
	}
	switch (tracer.action(&buffer))
	{
	case 1:
#if PRINT_SYNTAX
		PrintHandler::printParsingSuccessful();
#endif
		break;
	case -1:
		return -1;
	default:
		break;
	}
	return 0;
}

Parsing::Parsing()
{
}

Parsing::~Parsing()
{
}