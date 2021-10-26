#include "stdafx.h"
#include "Error.h"

Error::Error() : error(0)
{
}

void Error::reset()
{
	error = 0;
}