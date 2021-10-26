#pragma once
class WordHashing
{
public:
	static std::unordered_map<std::string, unsigned short> word;
};

enum class Symbol
{
	nul, //NULL

	ident,

	number,
	plus,
	minus,
	times,
	slash, /* / */
	eql,
	neq, /* # */
	lss,
	leq,
	gtr,
	geq,
	lparen,
	rparen,
	comma,
	semicolon,
	period,
	becomes,

	beginsym,
	endsym,
	ifsym,
	thensym,
	oddsym,
	whilesym,
	writesym,
	readsym,
	dosym,
	callsym,
	constsym,
	varsym,
	procsym
};