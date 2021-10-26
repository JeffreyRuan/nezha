#include "stdafx.h"
#include "PositionScan.h"
using namespace std;

PositionScan::PositionScan() :line(1), character(0)
{
}

void PositionScan::reportError()
{
	cout << format("line: {}, character: {}; error({}).", line, character, ++errorMangager.error) << endl;
}