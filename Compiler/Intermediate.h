#pragma once
#include "TraceElem.h"
#include "PositionScan.h"
#include "FTuple.h"

class Intermediate
{
private:
	static std::vector <FTuple>InterM_q;
	static std::map<std::string, std::string*> slots;
	static std::map<std::string, bool> defined;
	static std::stack<std::string*> temp;
	static int nextstat;
	static int merge(const int& _PreChain, const int& _PostChain);
	static void backpatch(const int& _Head, const int& _Targ);

	//Functions
	static void emit(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& result);
	static std::string newTemp();
	static std::string boolnameCvrt(const std::string& _N);
	static std::string* lookup(std::string ident_name);
	friend class Parsing;
	static void error(const int& _Id);
public:
	static void translate(std::vector<TraceElem>& _Pre, TraceElem* _Post, const int& _RulId);
};
