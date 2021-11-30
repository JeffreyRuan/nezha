#pragma once
enum class Type
{
	nul,
	integer,
	_bool,
	_char,
};
class Attribute
{
public:
	int _true;
	int _false;
	int _begin;
	Type type;
	std::string name;

	Attribute();
};
