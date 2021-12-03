#pragma once
#include "TraceElem.h"
#include "PositionScan.h"
#include "FTuple.h"

class Intermediate
{
private:
	static std::map<std::string, std::string*> slots;
	static std::map<std::string, bool> defined;
	static std::map<std::string, Type> type;
	static std::stack<std::string*> temp;
	static int lastCHAIN;
	static int nextstat;
	static int currRulId;

	//Functions
	static void emit(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& result);
	static std::string newTemp();
	static std::string boolnameCvrt(const std::string& _N);
	static std::string* lookup(std::string ident_name);
	static int merge(const int& _PreChain, const int& _PostChain);
	static void backpatch(const int& _Head, const int& _Targ);
	friend class Parsing;
	friend class Trace;
	static void error(const int& _Id);
public:
	static std::vector <std::pair<FTuple, int>>InterM_q;
	static void translate(std::vector<TraceElem>& R, TraceElem* L, const int& _RulId);
	static void finalPatch();
};
