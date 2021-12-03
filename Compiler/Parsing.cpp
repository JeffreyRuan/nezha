#include "stdafx.h"
#include"Parsing.h"
using namespace std;

void Parsing::processToken(const Lexical& lobj, const bool& keep_push)
{
	if (keep_push)
	{
		buffer.push(lobj.send);
	}
	if (tracer.action(&buffer) == 1)
	{
#if PRINT_SYNTAX
		PrintHandler::printParsingSuccessful();
#endif
	}
}

Parsing::Parsing()
{
}

Parsing::~Parsing()
{
}