#pragma once

#include "Globals.h"
#include "Card.h"

namespace BlackJack
{

	class Deck
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		Deck()
		{
			// Initialize deck
			for( uint suit = 0; suit < 4; ++suit )
				for( uint value = 2; value < 15; ++value )
					m_cards[ suit * 13 + value - 2 ] = Card( (Card::Suit)suit, (Card::Value)value );
		}

		/*************/
		/* Operators */
		/*************/
	public:
		Card operator[]( uint index ) 
		{
			return m_cards[ index ];
		}

		/********/
		/* Data */
		/********/
	private:
		Card    m_cards[ 52 ];
	};

}