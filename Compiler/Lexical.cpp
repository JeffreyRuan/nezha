#include "stdafx.h"
#include "Lexical.h"
using namespace std;

Lexical::Lexical(std::string l_doc) : ch('\0'), give_back('\0'), send(" "), sym(Symbol::nul), residue(false)
{
	fs.open(l_doc, ios::in);
}

Lexical::~Lexical()
{
	fs.close();
}

bool Lexical::isChar(const char& ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

Symbol Lexical::isKey(std::string store_str)
{
	//Find Keyword
	auto it = WordHashing::word.find(store_str);

	if (it != WordHashing::word.end())
	{
		return Symbol(it->second);
	}
	return Symbol::nul;
}

bool Lexical::isNum(const char& ch)
{
	return (ch >= '0' && ch <= '9');
}

int Lexical::getsym()
{
	//Reset
	store_str.clear();
	sym = Symbol::nul;
	unsigned int errortype = 0;

	//Get First Character
	getch();

	//Skip Space
	while (ch == ' ' || ch == 10 || ch == 13 || ch == 9)
	{
		getch();
	}

	//First ch isn't NULL
	if (ch != '\0')
	{
		if (isChar(ch))
		{
			while (!residue)
			{
				store_str.push_back(ch);

				// Is a Keyword
				sym = isKey(store_str);
				if (sym == Symbol::nul)
				{
					// Is an Identifier
					sym = Symbol::ident;
				}

				getch();
				if (!isChar(ch) && !isNum(ch))
				{
					give_back = ch;
					residue = true;
				}
			}
		}
		else if (isNum(ch))
		{
			while (!residue)
			{
				store_str.push_back(ch);

				//Is an Integer
				sym = Symbol::number;

				getch();
				if (!isNum(ch))
				{
					if (isChar(ch))
					{
						sym = Symbol::nul;
						errortype = 1;
					}
					give_back = ch;
					residue = true;
				}
			}
		}
		else if (ch == '\'')
		{
			bool rquotematch = false;
			do
			{
				store_str.push_back(ch);
				getch();
				if (ch == '\'')
				{
					//Is a string
					rquotematch = true;
					store_str.push_back(ch);
					sym = Symbol::charconst;
				}
				else if (ch == 10 || ch == 13 || ch == '\0')
				{
					//Is Return or End
					errortype = 2;
					break;
				}
			} while (!rquotematch);
		}

		else if (ch == '/')
		{
			store_str.push_back(ch);
			getch();
			if (ch == '*')
			{
				//Open Comment
				bool rcommentmatch = false;
				do
				{
					store_str.push_back(ch);
					getch();
					if (ch == '*')
					{
						store_str.push_back(ch);
						getch();
						if (ch == '/')
						{
							//Comment Closed
							store_str.push_back(ch);
							rcommentmatch = true;
							sym = Symbol::comment;
						}
						else if (ch == 10 || ch == 13 || ch == '\0')
						{
							//Is Return or End
							errortype = 3;
							break;
						}
					}
					else if (ch == 10 || ch == 13 || ch == '\0')
					{
						//Is Return or End
						errortype = 3;
						break;
					}
				} while (!rcommentmatch);
			}
			else
			{
				sym = Symbol::slash;
				give_back = ch;
				residue = true;
			}
		}

		else
		{
			// Is a Normal Delimiter
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

			case '.': store_str.push_back(ch); getch();
				if (ch == '.') { store_str.push_back(ch); sym = Symbol::dperiod; }
				else { sym = Symbol::period; give_back = ch; residue = true; } break;
			case '<': store_str.push_back(ch); getch();
				if (ch == '>') { store_str.push_back(ch); sym = Symbol::langle_rangle; }
				else if (ch == '=') { store_str.push_back(ch); sym = Symbol::langle_eql; }
				else { sym = Symbol::langle; give_back = ch; residue = true; } break;
			case '>': store_str.push_back(ch); getch();
				if (ch == '=') { store_str.push_back(ch); sym = Symbol::rangle_eql; }
				else { sym = Symbol::rangle; give_back = ch; residue = true; } break;
			case ':': store_str.push_back(ch); getch();
				if (ch == '=') { store_str.push_back(ch); sym = Symbol::colon_eql; }
				else { sym = Symbol::colon; give_back = ch; residue = true; } break;
			case '*': store_str.push_back(ch); getch();
				if (ch == '/') { store_str.push_back(ch); sym = Symbol::astrsk_slash; }
				else { sym = Symbol::astrsk; give_back = ch; residue = true; } break;
			default: store_str.push_back(ch); sym = Symbol::nul; errortype = 4; break;
			}
		}

		if (sym == Symbol::comment)
		{
		}
		else if (sym != Symbol::nul)
			PrintHandler::printLexicalDoublet(store_str, sym);
		else
			pos_scanner.reportError(errortype, store_str);
	}

	if (ch == '\0') return 1;
	return 0;
}

int Lexical::getch()
{
	if (residue)
	{
		ch = give_back;
		residue = false;
		return 0;
	}
	int pass = 0;
	if (!fs.get(ch))
	{
		ch = '\0';
		pass = 1;
	}
	if (ch == 10 || ch == 13)
	{
		pos_scanner.line++;
		pos_scanner.prevcharacter = pos_scanner.character;
		pos_scanner.character = 0;
	}
	else
	{
		pos_scanner.character++;
	}
	return pass;
}