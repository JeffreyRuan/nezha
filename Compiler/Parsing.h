#pragma once
#include "Lexical.h"
#include "Trace.h"
class Parsing {
private:
	Trace tracer;

public:
	std::queue<std::pair<int, int>>buffer;
	void processToken(const Lexical& lobj, const bool& keep_push);

	Parsing();
	~Parsing();
};
