#include "stdafx.h"
#include "Lexical.h"
using namespace std;

Lexical::Lexical(std::string l_doc) : ch('\0'), give_back('\0'), send_str(" "), sym(Symbol::nul), unusedch(false)
{
	fs.open(l_doc, ios::in);
}

bool Lexical::isChar(const char& ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

Symbol isKey(std::string store_str)
{
	//Find Keyword
	auto it = WordHashing::word.find(store_str);

	if (WordHashing::word.find(store_str) != WordHashing::word.end())
	{
		return Symbol(it->second);
	}
	return Symbol::nul;
}

bool isNum(const char& ch)
{
	return (ch >= '0' && ch <= '9');
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
	if (isChar(ch))
	{
		while (!unusedch)
		{
			store_str.push_back(ch);

			// Is a Keyword
			sym = isKey(store_str);
			if (sym != Symbol::nul) break;

			// Is an Identifier
			sym = Symbol::ident;

			getch();
			if (!isChar(ch) && !isNum(ch))
			{
				give_back = ch;
				unusedch = true;
			}
		}
	}
	else
	{
		// Is a Delimiter
		switch (ch)
		{
		case '+': sym = Symbol::plus; store_str.push_back(ch); break;
		case '-': sym = Symbol::minus; store_str.push_back(ch); break;
		case '=': sym = Symbol::eql; store_str.push_back(ch); break;
		case '(': sym = Symbol::lparen; store_str.push_back(ch); break;
		case ')': sym = Symbol::rparen; store_str.push_back(ch); break;
		case '[': sym = Symbol::lbrackt; store_str.push_back(ch); break;
		case ']': sym = Symbol::rbrackt; store_str.push_back(ch); break;
		case ';': sym = Symbol::semicolon; store_str.push_back(ch); break;
		case ',': sym = Symbol::comma; store_str.push_back(ch); break;

		case '/': store_str.push_back(ch); getch();
			if (ch == '*') { store_str.push_back(ch); sym = Symbol::slash_astrsk; }
			else { sym = Symbol::slash; give_back = ch; unusedch = true; } break;
		case '.': store_str.push_back(ch); getch();
			if (ch == '.') { store_str.push_back(ch); sym = Symbol::dperiod; }
			else { sym = Symbol::period; give_back = ch; unusedch = true; } break;
		case '<': store_str.push_back(ch); getch();
			if (ch == '>') { store_str.push_back(ch); sym = Symbol::langle_rangle; }
			else if (ch == '=') { store_str.push_back(ch); sym = Symbol::langle_eql; }
			else { sym = Symbol::langle; give_back = ch; unusedch = true; } break;
		case '>': store_str.push_back(ch); getch();
			if (ch == '=') { store_str.push_back(ch); sym = Symbol::rangle_eql; }
			else { sym = Symbol::rangle; give_back = ch; unusedch = true; } break;
		case ':': store_str.push_back(ch); getch();
			if (ch == '=') { store_str.push_back(ch); sym = Symbol::colon_eql; }
			else { sym = Symbol::colon; give_back = ch; unusedch = true; } break;
		case '*': store_str.push_back(ch); getch();
			if (ch == '/') { store_str.push_back(ch); sym = Symbol::astrsk_slash; }
			else { sym = Symbol::astrsk; give_back = ch; unusedch = true; } break;
		default: pos_scanner.reportError(); break;
		}
	}

	if (sym != Symbol::nul)
		PrintHandler::printLexicalDoublet(store_str, sym);

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