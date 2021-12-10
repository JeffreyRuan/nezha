#include "stdafx.h"
#include "PosParam.h"

PosParam::PosParam(int prevcharacter, int line, int character) :prevcharacter(prevcharacter), line(line), character(character)
{
}

void PosParam::set(int prevcharacter, int line, int character)
{
	this->prevcharacter = prevcharacter;
	this->line = line;
	this->character = character;
}