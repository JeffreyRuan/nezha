#include "stdafx.h"
#include "Lexical.h"
using namespace std;

Lexical::Lexical(std::string l_doc) : ch('\0'), id(""), sym(0)
{
	fs.open(l_doc, ios::in);
}

int Lexical::getsym()
{
	// Get First Symbol

	//Space or Tab etc.
	while (ch == 32 || ch == 10 || ch == 13 || ch == 9)
	{
		getch();
	}

	//Symbol Can Make a Word or Keyword
	if (ch >= 'a' && ch <= 'z')
	{
		token_str.push_back(ch);
		for (const auto& it : WordHashing::word)
		{
			if (it.first == token_str)
			{
				unsigned short t_id = it.second;

				// A Keyword
				if (t_id < 36) sym = t_id;

				// An Identifier
				else if (t_id == 36) sym = ident;

				break;
			}
		}
	}
}

int Lexical::getch()
{
	fs.get(ch);
}