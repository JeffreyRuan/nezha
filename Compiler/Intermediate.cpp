#include "stdafx.h"
#include "Intermediate.h"
using namespace std;

std::vector <FTuple> Intermediate::InterM_q;

int Intermediate::nextstat = 0;

std::map<std::string, std::string*> Intermediate::slots;

std::map<std::string, bool> Intermediate::defined;

std::map<std::string, Type> Intermediate::type;

std::stack<std::string*> Intermediate::temp;

//Functions
int Intermediate::merge(const int& _PreChain, const int& _PostChain)
{
	if (_PostChain == 0)
	{
		return _PreChain;
	}
	int bf, aft;
	bf = aft = _PostChain;
	while (true)
	{
		aft = atoi(InterM_q[bf].result.c_str());
		if (aft == 0)
		{
			break;
		}
		bf = aft;
	}
	InterM_q[bf].result = to_string(_PreChain);
	return _PostChain;
}

void Intermediate::backpatch(const int& _Head, const int& _Targ)
{
	int bf, aft;
	bf = aft = _Head;
	while (true)
	{
		aft = atoi(InterM_q[bf].result.c_str());
		if (aft == 0)
		{
			break;
		}
		InterM_q[bf].result = to_string(_Targ);
		bf = aft;
	}
	InterM_q[bf].result = to_string(_Targ);
}

std::string Intermediate::newTemp()
{
	temp.push(new std::string("T" + to_string(temp.size())));
	return *temp.top();
}

std::string Intermediate::boolnameCvrt(const std::string& _N)
{
	if (_N == "true")
	{
		return "1";
	}
	if (_N == "false")
	{
		return "0";
	}

	cerr << "The name has no relationships with boolean stuffs." << endl;
}

void Intermediate::emit(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& result)
{
	FTuple t_tpl = { op, arg1, arg2, result };
	InterM_q.emplace_back(t_tpl);
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

void Intermediate::translate(std::vector<TraceElem>& R, TraceElem* L, const int& _RulId)
{
	switch (_RulId)
	{
		//Arithmetic Expression
	case 12:
	{
		L->attr.name = newTemp();
		emit(":=", R[0].attr.name, "-", L->attr.name);
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
				L->attr.name = *p;
			}
			else
			{
				error(8);
			}
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
			L->attr._false = 0;
		}
		else if (t_str == "false")
		{
			L->attr._true = 0;
			L->attr._false = nextstat;
		}
		emit("jump", "-", "-", "0");

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
				L->attr.name = *p;
			}
			else
			{
				error(8);
			}
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
		emit("j" + R[1].attr.name, R[0].attr.name, R[2].attr.name, "0");
		emit("jump", "-", "-", "0");
		break;
	}
	case 25:
	{
		L->attr._codebegin = nextstat;
		L->attr._true = nextstat;
		L->attr._false = nextstat + 1;
		emit("j" + R[1].attr.name, R[0].attr.name, R[2].attr.name, "0");
		emit("jump", "-", "-", "0");
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
		L->attr.name = newTemp();
		emit(":=", R[0].attr.name, "-", L->attr.name);
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
				L->attr.name = *p;
			}
			else
			{
				error(8);
			}
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
		emit("jump", "-", "-", "0");
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
		backpatch(R[1].attr._true, nextstat);
		L->attr.CHAIN = R[1].attr._false;
		break;
	}
	case 39:
	{
		backpatch(R[1].attr.CHAIN, R[0].attr._codebegin);
		emit("jump", "-", "-", to_string(R[0].attr._codebegin));
		L->attr.CHAIN = R[0].attr.CHAIN;
		break;
	}

	//REPEAT Statement
	case 44:
	{
		backpatch(R[1].attr.CHAIN, R[3].attr._codebegin);
		backpatch(R[3].attr._true, nextstat);
		emit("jump", "-", "-", to_string(R[1].attr._codebegin));
		L->attr.CHAIN = R[3].attr._false;
		break;
	}

	//BEGIN_END
	case 45:
	{
		L->attr.CHAIN = R[1].attr.CHAIN;
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
		string* p = lookup(L->attr.name);
		if (p != nullptr)
		{
			//Has Been Declared
			if (L->attr.type != R[0].attr.type)
			{
				error(9);
			}
			else
			{
				switch (type[L->attr.name])
				{
				case Type::integer:
				{
					emit(":=", R[0].attr.name, "-", *p);
					defined[L->attr.name] = true;
					break;
				}
				case Type::_bool:
				{
					backpatch(R[0].attr._true, nextstat);
					emit(":=", "1", "-", L->attr.name);
					backpatch(R[0].attr._false, nextstat);
					emit(":=", "0", "-", L->attr.name);
					defined[L->attr.name] = true;
					break;
				}
				case Type::_char:
				{
					emit(":=", R[0].attr.name, "-", *p);
					defined[L->attr.name] = true;
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
		L->attr.CHAIN = 0;
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
	case 0: break;
		//Reduce Error
	default:cerr << "Invalid rule ID." << endl; break;
	}
}