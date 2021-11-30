#pragma once
class LexStore
{
private:
	friend class Trace;
public:
	static std::map<std::string, unsigned int> storemap;
};
