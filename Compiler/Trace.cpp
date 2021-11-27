#include "stdafx.h"
#include "Trace.h"
using namespace std;

void Trace::reduce(const std::string& to_do)
{
	int n = ReduceTable::R_backLen[to_do];
	for (int i = 0; i < n; i++)
	{
		traceStack.pop();
	}

	string matchedNT = ReduceTable::R_NonTermnl[to_do];
	string steady_s = LR_Table::m_lrmap[matchedNT][traceStack.top().status];
	TraceElem t_e = { atoi(steady_s.c_str()), pair<int, int>(0, -1), matchedNT };
	traceStack.push(t_e);
}

std::string Trace::identDoubletToString(const std::pair<int, int>& l_doublet)
{
	return find_if(Store::storemap.begin(), Store::storemap.end(), [&](const std::map<string, unsigned int>::value_type& pair) {return pair.second == l_doublet.second; })->first;
}

Trace::Trace()
{
	//Push base status into the trace stack
	TraceElem t_e = { 0, pair<int, int>(0, -1), "_base" };
	traceStack.push(t_e);
}

int Trace::action(std::queue<std::pair<int, int>>* l_buffer)
{
	int top = traceStack.top().status;
	std::string t_token = SymbolList::words[l_buffer->front().first];
	string to_do = LR_Table::m_lrmap[t_token][top];

	if (to_do.front() == 'r')
	{
		reduce(to_do);
	}
	else if (to_do.front() == 'e')
	{
		pos_scanner.reportError(5, identDoubletToString(l_buffer->front()));
		//Panic-mode recovery
	}
	else if (to_do == "acc")
	{
		l_buffer->pop();
		return 1;
	}
	else
	{
		int i_to_do = std::atoi(to_do.c_str());
		TraceElem t_e = { i_to_do, l_buffer->front(), identDoubletToString(l_buffer->front()) };
		traceStack.push(t_e);
		l_buffer->pop();
	}

	PrintHandler::printParsingAction(t_token, traceStack.top(), to_do);
	return 0;
}