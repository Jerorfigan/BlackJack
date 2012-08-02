#include "stdafx.h"

#define GLOBAL_DEF

#include "Globals.h"

namespace BlackJack
{

	/********************/
	/* Global functions */
	/********************/
	int RandomBetween( int low, int high, bool inclusive )
	{
		if( inclusive )
		{
			return low + rand() % ( high - low + 1 );
		}
		else
		{
			return low + rand() % ( high - low - 1 ) + 1;
		}
	}

}