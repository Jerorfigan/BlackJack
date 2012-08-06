#pragma once

/*****************/
/*****************/
/* Global stuff. */
/*****************/
/*****************/

#include <string>
#include <sstream>

namespace BlackJack
{

	/************/
	/* Typedefs */
	/************/
	typedef unsigned int uint;

	/********************/
	/* Global functions */
	/********************/
	int RandomBetween( int low, int high, bool inclusive = true );
	
	template < typename numericType >
	std::string NumToStr( numericType num )
	{
		std::stringstream s;
		s << num;
		return s.str();
	}
}