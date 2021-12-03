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
		PrintHandler::printParsingSuccessful();
	}
}

Parsing::Parsing()
{
}

Parsing::~Parsing()
{
}