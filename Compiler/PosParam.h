#pragma once
class PosParam
{
public:
	int prevcharacter;
	int line;
	int character;
	PosParam(int prevcharacter, int line, int character);
	void set(int prevcharacter, int line, int character);
};
