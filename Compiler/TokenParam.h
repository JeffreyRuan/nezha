#pragma once
#include "PosParam.h"

class TokenParam
{
public:
	std::pair<int, int> doublet;
	PosParam pos;
	TokenParam(std::pair<int, int> doublet, PosParam pos);
};
