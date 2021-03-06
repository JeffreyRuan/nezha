#include "stdafx.h"
#include "Intermediate.h"
using namespace std;

std::vector <std::pair<FTuple, int>> Intermediate::InterM_q;

int Intermediate::nextstat = 0;

int Intermediate::currRulId = 0;

std::string Intermediate::programName;

std::map<std::string, std::string*> Intermediate::slots;

std::map<std::string, bool> Intermediate::defined;

std::map<std::string, Type> Intermediate::type;

std::stack<std::string*> Intermediate::temp;

int Intermediate::lastCHAIN = -1;

//Functions
int Intermediate::merge(const int& _PreChain, const int& _PostChain)
{
	if (_PostChain == -1)
	{
		return _PreChain;
	}
	int bf, aft;
	bf = aft = _PostChain;
	while (true)
	{
		aft = atoi(InterM_q[bf].first.result.c_str());
		if (aft == -1)
		{
			break;
		}
		bf = aft;
	}
	InterM_q[bf].first.result = to_string(_PreChain);
	return _PostChain;
}
void Intermediate::backpatch(const int& _Head, const int& _Targ)
{
	int bf, aft;
	bf = aft = _Head;
	if (bf == -1)
	{
		return;
	}
	while (true)
	{
		aft = atoi(InterM_q[bf].first.result.c_str());
		if (aft == -1)
		{
			break;
		}
		InterM_q[bf].first.result = to_string(_Targ);
		bf = aft;
	}
	InterM_q[bf].first.result = to_string(_Targ);
}

std::string Intermediate::newTemp()
{
	temp.push(new std::string("T" + to_string(temp.size() + 1)));
	type.insert(std::pair<std::string, Type>(*temp.top(), Type::integer));
	return *temp.top();
}

void Intermediate::emit(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& result)
{
	FTuple t_tpl = { op, arg1, arg2, result };
	InterM_q.emplace_back(std::pair<FTuple, int>(t_tpl, currRulId));
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
	PositionScan::reportError(_Id, Trace::m_Pos.line, Trace::m_Pos.prevcharacter, Trace::m_Pos.character);
}

void Intermediate::translate(std::vector<TraceElem>& R, TraceElem* L, const int& _RulId)
{
	//Update currRulId
	currRulId = _RulId;

	switch (_RulId)
	{
		//Arithmetic Expression
	case 12:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 13:
	{
		string* p = lookup(R[0].attr.name);
		if (p != nullptr)
		{
			//Identifier Has Declared
			if (defined[*p])
			{
				if (type[*p] != Type::integer)
				{
					error(9);
				}
			}
			else
			{
				error(8);
			}
			L->attr.name = *p;
		}
		else
		{
			error(7);
		}
		break;
	}
	case 14:
	{
		L->attr.name = R[1].attr.name;
		break;
	}
	case 10:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 11:
	{
		L->attr.name = newTemp();
		emit("@", R[1].attr.name, "-", L->attr.name);
		break;
	}
	case 7:
	{
		L->attr.name = newTemp();
		emit("*", R[0].attr.name, R[2].attr.name, L->attr.name);
		break;
	}
	case 8:
	{
		L->attr.name = newTemp();
		emit("/", R[0].attr.name, R[2].attr.name, L->attr.name);
		break;
	}
	case 9:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 4:
	{
		L->attr.name = newTemp();
		emit("+", R[0].attr.name, R[2].attr.name, L->attr.name);
		break;
	}
	case 5:
	{
		L->attr.name = newTemp();
		emit("-", R[0].attr.name, R[2].attr.name, L->attr.name);
		break;
	}
	case 6:
	{
		L->attr.name = R[0].attr.name;
		break;
	}

	//Boolean Expression
	case 26:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 27:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 28:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 29:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 30:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 31:
	{
		L->attr.name = R[0].attr.name;
		break;
	}

	case 21:
	{
		string t_str = R[0].attr.name;

		L->attr._codebegin = nextstat;
		if (t_str == "true")
		{
			L->attr._true = nextstat;
			L->attr._false = -1;
		}
		else if (t_str == "false")
		{
			L->attr._true = -1;
			L->attr._false = nextstat;
		}
		emit("j", "-", "-", "-1");

		break;
	}
	case 22:
	{
		string* p = lookup(R[0].attr.name);
		if (p != nullptr)
		{
			//Identifier Has Assigned
			if (defined[*p])
			{
				if (type[*p] != Type::_bool)
				{
					error(9);
				}
			}
			else
			{
				error(8);
			}
			L->attr.name = *p;
		}
		else
		{
			error(7);
		}
		break;
	}
	case 23:
	{
		L->attr._codebegin = R[1].attr._codebegin;
		L->attr._true = R[1].attr._true;
		L->attr._false = R[1].attr._false;
		break;
	}
	case 24:
	{
		L->attr._codebegin = nextstat;
		L->attr._true = nextstat;
		L->attr._false = nextstat + 1;
		emit("j" + R[1].attr.name, R[0].attr.name, R[2].attr.name, "-1");
		emit("j", "-", "-", "-1");
		break;
	}
	case 25:
	{
		L->attr._codebegin = nextstat;
		L->attr._true = nextstat;
		L->attr._false = nextstat + 1;
		emit("j" + R[1].attr.name, R[0].attr.name, R[2].attr.name, "-1");
		emit("j", "-", "-", "-1");
		break;
	}

	case 19:
	{
		L->attr._codebegin = R[0].attr._codebegin;
		L->attr._true = R[0].attr._true;
		L->attr._false = R[0].attr._false;
		break;
	}
	case 20:
	{
		L->attr._codebegin = R[1].attr._codebegin;
		L->attr._true = R[1].attr._false;
		L->attr._false = R[1].attr._true;
		break;
	}

	case 17:
	{
		L->attr._codebegin = R[0].attr._codebegin;
		backpatch(R[0].attr._true, R[2].attr._codebegin);
		L->attr._true = R[2].attr._true;
		L->attr._false = merge(R[0].attr._false, R[2].attr._false);
		break;
	}
	case 18:
	{
		L->attr._codebegin = R[0].attr._codebegin;
		L->attr._true = R[0].attr._true;
		L->attr._false = R[0].attr._false;
		break;
	}

	case 15:
	{
		L->attr._codebegin = R[0].attr._codebegin;
		backpatch(R[0].attr._false, R[2].attr._codebegin);
		L->attr._true = merge(R[0].attr._true, R[2].attr._true);
		L->attr._false = R[2].attr._false;
		break;
	}
	case 16:
	{
		L->attr._codebegin = R[0].attr._codebegin;
		L->attr._true = R[0].attr._true;
		L->attr._false = R[0].attr._false;
		break;
	}

	//Char Expression
	case 32:
	{
		L->attr.name = R[0].attr.name;
		break;
	}
	case 33:
	{
		string* p = lookup(R[0].attr.name);
		if (p != nullptr)
		{
			//Identifier Has Assigned
			if (defined[*p])
			{
				if (type[*p] != Type::_char)
				{
					error(9);
				}
			}
			else
			{
				error(8);
			}
			L->attr.name = *p;
		}
		else
		{
			error(7);
		}
		break;
	}

	//IF Statement
	case 40:
	{
		backpatch(R[1].attr._true, nextstat);
		L->attr.CHAIN = R[1].attr._false;
		break;
	}
	case 37:
	{
		L->attr.CHAIN = merge(R[0].attr.CHAIN, R[1].attr.CHAIN);
		break;
	}
	case 41:
	{
		int tmp = nextstat;
		emit("j", "-", "-", "-1");
		backpatch(R[0].attr.CHAIN, nextstat);
		L->attr.CHAIN = merge(tmp, R[1].attr.CHAIN);
		break;
	}
	case 38:
	{
		L->attr.CHAIN = merge(R[0].attr.CHAIN, R[1].attr.CHAIN);
		break;
	}

	//WHILE Statement
	case 43:
	{
		L->attr._codebegin = nextstat;
		break;
	}
	case 42:
	{
		L->attr._codebegin = R[0].attr._codebegin;
		backpatch(R[1].attr._true, nextstat);
		L->attr.CHAIN = R[1].attr._false;
		break;
	}
	case 39:
	{
		backpatch(R[1].attr.CHAIN, R[0].attr._codebegin);
		emit("j", "-", "-", to_string(R[0].attr._codebegin));
		L->attr.CHAIN = R[0].attr.CHAIN;
		break;
	}

	//REPEAT Statement
	case 57:
	{
		L->attr._codebegin = nextstat;
		break;
	}
	case 44:
	{
		backpatch(R[1].attr.CHAIN, R[3].attr._codebegin);
		backpatch(R[3].attr._false, R[0].attr._codebegin);
		L->attr.CHAIN = R[3].attr._true;
		break;
	}

	//BEGIN_END
	case 45:
	{
		lastCHAIN = L->attr.CHAIN = R[1].attr.CHAIN;
		break;
	}
	case 35:
	{
		L->attr.CHAIN = R[0].attr.CHAIN;
		break;
	}

	//Assignment
	case 1:
	{
		L->attr.type = Type::integer;
		L->attr.name = R[0].attr.name;
		break;
	}
	case 2:
	{
		L->attr.type = Type::_bool;
		L->attr._true = R[0].attr._true;
		L->attr._false = R[0].attr._false;
		break;
	}
	case 3:
	{
		L->attr.type = Type::_char;
		L->attr.name = R[0].attr.name;
		break;
	}
	case 36:
	{
		string* p = lookup(R[0].attr.name);
		if (p != nullptr)
		{
			//Has Been Declared
			//If the types aren't matched, error
			if (!(type[R[0].attr.name] == type[R[2].attr.name] || type[R[0].attr.name] == R[2].attr.type))
			{
				error(9);
			}
			else
			{
				switch (type[R[0].attr.name])
				{
				case Type::integer:
				{
					emit(":=", R[2].attr.name, "-", *p);
					defined[R[0].attr.name] = true;
					break;
				}
				case Type::_bool:
				{
					backpatch(R[2].attr._true, nextstat);
					emit(":=", "1", "-", R[0].attr.name);
					emit("j", "-", "-", to_string(nextstat + 2));
					backpatch(R[2].attr._false, nextstat);
					emit(":=", "0", "-", R[0].attr.name);
					defined[R[0].attr.name] = true;
					break;
				}
				case Type::_char:
				{
					emit(":=", R[2].attr.name, "-", *p);
					defined[R[0].attr.name] = true;
					break;
				}
				default: break;
				}
			}
		}
		else
		{
			error(8);
		}
		break;
	}
	case 34:
	{
		L->attr.CHAIN = -1;
		break;
	}

	//Statement List
	case 48:
	{
		L->attr.CHAIN = R[0].attr.CHAIN;
		break;
	}
	case 46:
	{
		backpatch(R[0].attr.CHAIN, nextstat);
		break;
	}
	case 47:
	{
		L->attr.CHAIN = R[1].attr.CHAIN;
		break;
	}

	//Var Declare
	case 54:
	{
		string* p = lookup(R[0].attr.name);
		if (p != nullptr)
		{
			//Already Been Declared
			error(10);
		}
		else
		{
			slots.insert(std::pair<std::string, std::string*>(R[0].attr.name, new string(R[0].attr.name)));
			defined.insert(std::pair<std::string, bool>(R[0].attr.name, false));
			type.insert(std::pair<std::string, Type>(R[0].attr.name, Type::integer));
			L->attr.type = Type::integer;
		}
		break;
	}
	case 55:
	{
		string* p = lookup(R[0].attr.name);
		if (p != nullptr)
		{
			//Already Been Declared
			error(10);
		}
		else
		{
			slots.insert(std::pair<std::string, std::string*>(R[0].attr.name, new string(R[0].attr.name)));
			defined.insert(std::pair<std::string, bool>(R[0].attr.name, false));
			type.insert(std::pair<std::string, Type>(R[0].attr.name, Type::_bool));
			L->attr.type = Type::_bool;
		}
		break;
	}
	case 56:
	{
		string* p = lookup(R[0].attr.name);
		if (p != nullptr)
		{
			//Already Been Declared
			error(10);
		}
		else
		{
			slots.insert(std::pair<std::string, std::string*>(R[0].attr.name, new string(R[0].attr.name)));
			defined.insert(std::pair<std::string, bool>(R[0].attr.name, false));
			type.insert(std::pair<std::string, Type>(R[0].attr.name, Type::_char));
			L->attr.type = Type::_char;
		}
		break;
	}
	case 53:
	{
		string* p = lookup(R[0].attr.name);
		if (p != nullptr)
		{
			//Already Been Declared
			error(10);
		}
		else
		{
			slots.insert(std::pair<std::string, std::string*>(R[0].attr.name, new string(R[0].attr.name)));
			defined.insert(std::pair<std::string, bool>(R[0].attr.name, false));
			type.insert(std::pair<std::string, Type>(R[0].attr.name, R[2].attr.type));
			L->attr.type = R[2].attr.type;
		}
		break;
	}
	case 49: break;
	case 50: break;
	case 51: break;
	case 52: break;

		//Program
	case 0:
	{
		programName = R[1].attr.name;
		break;
	}

	//Reduce Error
	default:cerr << "Invalid rule ID." << endl; break;
	}
}

void Intermediate::finalPatch()
{
	backpatch(lastCHAIN, nextstat);
	emit("sys", "-", "-", "-");
}