#pragma once
#include "LR_Table.h"
#include "PositionScan.h"
#include "SymbolList.h"
#include "ReduceTable.h"
#include "Store.h"
#include "TraceElem.h"

class Trace
{
private:
	std::stack<TraceElem>traceStack;
	PositionScan pos_scanner;
	void reduce(const std::string& to_do);
	static std::string identDoubletToString(const std::pair<int, int>& l_doublet);

public:
	Trace();
	int action(std::queue<std::pair<int, int>>* l_buffer);
};
