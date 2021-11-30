#include "stdafx.h"
#include "Intermediate.h"
using namespace std;

std::queue <FTuple> Intermediate::InterM_q;

int Intermediate::nextstat = 0;

std::map<std::string, std::string*> Intermediate::slots;

std::stack<std::string*> Intermediate::temp;

//Functions

std::string Intermediate::newTemp()
{
	temp.push(new std::string("T" + to_string(temp.size())));
	return *temp.top();
}

void Intermediate::emit(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& result)
{
	FTuple t_tpl = { op, arg1, arg2, result };
	InterM_q.push(t_tpl);
	nextstat++;
}

std::string* Intermediate::lookup(std::string ident_name)
{
	auto it = slots.find(ident_name);

	if (it != slots.end())
	{
		return it->second;
	}
	return nullptr;
}

void Intermediate::error(const int& _Id)
{
	PositionScan::reportError(_Id);
}

void Intermediate::translate(std::vector<TraceElem>& _Pre, TraceElem* _Post, const int& _RulId)
{
	switch (_RulId)
	{
		//Arithmetic Expression
	case 12:
	{
		_Post->attr.name = newTemp();
		emit(":=", _Pre[0].attr.name, "-", _Post->attr.name);
		break;
	}
	case 13:
	{
		string* p = lookup(_Pre[0].attr.name);
		if (p != nullptr)
		{
			_Post->attr.name = *p;
		}
		else
		{
			error(6);
		}
		break;
	}
	case 14:
	{
		_Post->attr.name = _Pre[1].attr.name;
		break;
	}
	case 10:
	{
		_Post->attr.name = _Pre[0].attr.name;
		break;
	}
	case 11:
	{
		_Post->attr.name = newTemp();
		emit("@", _Pre[1].attr.name, "-", _Post->attr.name);
		break;
	}
	case 7:
	{
		_Post->attr.name = newTemp();
		emit("*", _Pre[0].attr.name, _Pre[2].attr.name, _Post->attr.name);
		break;
	}
	case 8:
	{
		_Post->attr.name = newTemp();
		emit("/", _Pre[0].attr.name, _Pre[2].attr.name, _Post->attr.name);
		break;
	}
	case 9:
	{
		_Post->attr.name = _Pre[0].attr.name;
		break;
	}
	case 4:
	{
		_Post->attr.name = newTemp();
		emit("+", _Pre[0].attr.name, _Pre[2].attr.name, _Post->attr.name);
		break;
	}
	case 5:
	{
		_Post->attr.name = newTemp();
		emit("-", _Pre[0].attr.name, _Pre[2].attr.name, _Post->attr.name);
		break;
	}
	case 6:
	{
		_Post->attr.name = _Pre[0].attr.name;
		break;
	}

	//Reduce Error
	default:throw("Something was not right."); break;
	}
}