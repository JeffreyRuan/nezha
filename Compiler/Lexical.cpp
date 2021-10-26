#include "stdafx.h"
#include "Lexical.h"
using namespace std;

Lexical::Lexical(std::string l_doc) : ch('\0'), give_back('\0'), send_str(" "), sym(Symbol::nul), unusedch(false)
{
	fs.open(l_doc, ios::in);
}

int Lexical::getsym()
{
	//Reset
	store_str.clear();
	sym = Symbol::nul;

	//Get First Character
	getch();

	//Skip Space
	while (ch == ' ' || ch == 10 || ch == 13 || ch == 9)
	{
		getch();
	}

	//Symbol Can Make an Identifier or Keyword
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		do
		{
			store_str.push_back(ch);

			//Find Keyword
			auto it = WordHashing::word.find(store_str);
			// Is a Keyword
			if (WordHashing::word.find(store_str) != WordHashing::word.end())
			{
				sym = Symbol(it->second);
			}

			// Is an Identifier
			sym = Symbol::ident;

			getch();
		} while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'));
	}
	else
	{
		// Is a Delimiter
		switch (ch)
		{
		case '+': sym = Symbol::plus; break;
		case '-': sym = Symbol::minus; break;
		case '=': sym = Symbol::eql; break;
		case '(': sym = Symbol::lparen; break;
		case ')': sym = Symbol::rparen; break;
		case '[': sym = Symbol::lbrackt; break;
		case ']': sym = Symbol::rbrackt; break;
		case ';': sym = Symbol::semicolon; break;
		case ',': sym = Symbol::comma; break;

		case '/': getch();
			if (ch == '*') sym = Symbol::slash_astrsk;
			else { sym = Symbol::slash; give_back = ch; unusedch = true; } break;
		case '.': getch();
			if (ch == '.') sym = Symbol::dperiod;
			else { sym = Symbol::period; give_back = ch; unusedch = true; } break;
		case '<': getch();
			if (ch == '>') sym = Symbol::langle_rangle;
			else if (ch == '=') sym = Symbol::langle_eql;
			else { sym = Symbol::langle; give_back = ch; unusedch = true; } break;
		case '>': getch();
			if (ch == '=') sym = Symbol::rangle_eql;
			else { sym = Symbol::rangle; give_back = ch; unusedch = true; } break;
		case ':': getch();
			if (ch == '=') sym = Symbol::colon_eql;
			else { sym = Symbol::colon; give_back = ch; unusedch = true; } break;
		case '*': getch();
			if (ch == '/') sym = Symbol::astrsk_slash;
			else { sym = Symbol::astrsk; give_back = ch; unusedch = true; } break;
		default: pos_scanner.reportError(); break;
		}
	}

	return 0;
}

int Lexical::getch()
{
	if (unusedch)
	{
		ch = give_back;
		unusedch = false;
		return 0;
	}

	int pass = 0;
	if (!fs.get(ch)) pass = 1;
	if (ch == 10 || ch == 13)
	{
		pos_scanner.line++;
		pos_scanner.character = 0;
	}
	else
	{
		pos_scanner.character++;
	}
	return pass;
}