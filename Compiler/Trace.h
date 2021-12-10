#pragma once
#include "LR_Table.h"
#include "PositionScan.h"
#include "ValidToken.h"
#include "ReduceTable.h"
#include "LexStore.h"
#include "TraceElem.h"
#include "Intermediate.h"
#include "TokenParam.h"

class Trace
{
private:
	std::stack<TraceElem>traceStack;
	void reduce(const std::string& to_do);
	static std::string identDoubletToString(const std::pair<int, int>& l_doublet);

public:
	static PosParam m_Pos;
	Trace();
	int action(std::queue<TokenParam>* l_buffer);
};
