#pragma once
#include "TraceElem.h"
#include "PositionScan.h"
#include "FTuple.h"

class Intermediate
{
private:
	static std::queue <FTuple>InterM_q;
	static std::map<std::string, std::string*> slots;
	static std::stack<std::string*> temp;
	static int nextstat;

	//Functions
	static void emit(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& result);
	static std::string newTemp();
	static std::string* lookup(std::string ident_name);
	friend class Parsing;
	static void error(const int& _Id);
public:
	static void translate(std::vector<TraceElem>& _Pre, TraceElem* _Post, const int& _RulId);
};
