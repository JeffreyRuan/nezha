#pragma once
class WordHashing
{
public:
	static std::unordered_map<std::string, unsigned short> word;
	static std::unordered_map<std::string, unsigned short> delimitsym;
};

enum class Symbol
{
	//Keyword
	andsym = 1,
	arraysym,
	beginsym,
	boolsym,
	callsym,
	casesym,
	charsym,
	constantsym,
	dimsym,
	dosym,
	elsesym,
	endsym,
	falsesym,
	forsym,
	ifsym,
	inputsym,
	integersym,
	notsym,
	ofsym,
	orsym,
	outputsym,
	proceduresym,
	programsym,
	readsym,
	realsym,
	repeatsym,
	setsym,
	stopsym,
	thensym,
	tosym,
	truesym,
	untilsym,
	varsym,
	whilesym,
	writesym,

	ident,
	number,
	charconst,

	lparen, /* ( */
	rparen, /* ) */
	astrsk, // * //
	astrsk_slash, // */ //
	plus, // + //
	comma, // , //
	minus, // - //
	period, // . //
	dperiod, // .. //
	slash, /* / */
	slash_astrsk, // /* //
	colon, // : //
	colon_eql, // := //
	semicolon, // ; //
	langle, // < //
	langle_eql, // <= //
	langle_rangle, // <> //
	eql, // = //
	rangle, // > //
	rangle_eql, // >= //
	lbrackt, /* [ */
	rbrackt, /* ] */

	nul, //NULL
};
