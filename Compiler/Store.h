#pragma once
class Store
{
private:
	friend class Trace;
public:
	static std::map<std::string, unsigned int> storemap;
};
