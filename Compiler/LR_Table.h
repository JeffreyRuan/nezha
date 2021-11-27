#pragma once
class LR_Table
{
private:
	static std::unordered_map<std::string, std::vector<std::string>>m_lrmap;
	friend class Trace;
};
