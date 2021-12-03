#include "stdafx.h"
#include "Trace.h"
using namespace std;

void Trace::reduce(const std::string& to_do)
{
	int n = ReduceTable::R_backLen[to_do];
	stack<TraceElem>t_s;
	for (int i = 0; i < n; i++)
	{
		t_s.push(traceStack.top());
		traceStack.pop();
	}
	vector<TraceElem>t_v;
	for (int i = 0; i < n; i++)
	{
		t_v.emplace_back(t_s.top());
		t_s.pop();
	}
	string matchedNT = ReduceTable::R_NonTermnl[to_do];
	string steady_s = LR_Table::m_lrmap[matchedNT][traceStack.top().status];
	TraceElem t_e(atoi(steady_s.c_str()), pair<int, int>(0, -1), matchedNT, Attribute());
	traceStack.push(t_e);

	//Adjust to_do to permitted integer
	int t_numberpart = atoi(to_do.substr(1, to_do.size() - 1).c_str());
	Intermediate::translate(t_v, &traceStack.top(), t_numberpart);
}

std::string Trace::identDoubletToString(const std::pair<int, int>& l_doublet)
{
	return find_if(LexStore::storemap.begin(), LexStore::storemap.end(), [&](const std::map<string, unsigned int>::value_type& pair) {return pair.second == l_doublet.second; })->first;
}

Trace::Trace()
{
	//Push base status into the trace stack
	TraceElem t_e(0, pair<int, int>(0, -1), "_base", Attribute());
	traceStack.push(t_e);
}

int Trace::action(std::queue<std::pair<int, int>>* l_buffer)
{
	int top = traceStack.top().status;
	std::string t_token = ValidToken::words[l_buffer->front().first];
	string to_do = LR_Table::m_lrmap[t_token][top];

	//r..
	if (to_do.front() == 'r')
	{
		reduce(to_do);
	}
	//d1
	else if (to_do == "d1")
	{
		switch (Intermediate::type[traceStack.top().attr.name])
		{
		case Type::integer: reduce("r13"); break;
		case Type::_bool: reduce("r22"); break;
		case Type::_char: reduce("r33"); break;
		default: pos_scanner.reportError(6); break;
		}
	}
	//d2
	else if (to_do == "d2")
	{
		switch (Intermediate::type[traceStack.top().attr.name])
		{
		case Type::integer: reduce("r13"); break;
		case Type::_bool: reduce("r22"); break;
		default: pos_scanner.reportError(6); break;
		}
	}
	//error
	else if (to_do.front() == 'e')
	{
		pos_scanner.reportError(5);
		//Panic-mode recovery
	}
	//acc
	else if (to_do == "acc")
	{
		l_buffer->pop();
		return 1;
	}
	//s..
	else
	{
		int i_to_do = std::atoi(to_do.c_str());
		TraceElem* t_e;
		int& wordnum = l_buffer->front().first;
		//identifier, number or string
		if (wordnum == 36 || wordnum == 37 || wordnum == 38)
		{
			t_e = new TraceElem(i_to_do, l_buffer->front(), identDoubletToString(l_buffer->front()), Attribute());
		}
		//word is "false"
		else if (wordnum == 13)
		{
			t_e = new TraceElem(i_to_do, l_buffer->front(), "false", Attribute());
		}
		//word is "true"
		else if (wordnum == 31)
		{
			t_e = new TraceElem(i_to_do, l_buffer->front(), "true", Attribute());
		}
		//other keywords
		else
		{
			t_e = new TraceElem(i_to_do, l_buffer->front(), ValidToken::words[l_buffer->front().first], Attribute());
		}

		traceStack.push(*t_e);
		l_buffer->pop();
		delete t_e;
	}
#if PRINT_SYNTAX
	PrintHandler::printParsingAction(t_token, traceStack.top(), to_do);
#endif
	return 0;
}