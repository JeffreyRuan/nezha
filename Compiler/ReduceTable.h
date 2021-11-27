#pragma once
class ReduceTable
{
private:
	static std::unordered_map<std::string, int>R_backLen;
	static std::unordered_map<std::string, std::string>R_NonTermnl;
	friend class Trace;
};
