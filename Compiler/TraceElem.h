#pragma once
#include "Attribute.h"

class TraceElem
{
public:
	int status;
	std::pair<int, int> doublet;
	std::string label;
	Attribute attr;
	TraceElem(int status, std::pair<int, int> doublet, std::string label, Attribute attr) :status(status), doublet(doublet), label(label), attr(attr)
	{
		this->attr.name = this->label;
	}
};
