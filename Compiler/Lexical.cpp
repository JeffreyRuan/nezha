#include "stdafx.h"
#include "Lexical.h"
using namespace std;

Lexical::Lexical(std::string l_doc) : ch('\0'), send_str(" "), sym(Symbol::nul)
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

	//Skip Delimiter
	while (ch == ' ' || ch == 9 || ch == 13 || ch == 9)
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

		send_str = store_str;
	}
	else
	{
		pos_scanner.reportError();
	}
	return 0;
}

int Lexical::getch()
{
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