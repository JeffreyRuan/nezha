#pragma once
#include "Lexical.h"
#include "Trace.h"
#include "TokenParam.h"
class Parsing {
private:
	Trace tracer;

public:
	std::queue<TokenParam>buffer;
	void processToken(const Lexical& lobj, const bool& keep_push);

	Parsing();
	~Parsing();
};
