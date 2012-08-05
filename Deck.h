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
			for( uint suit = 1; suit < 5; ++suit )
				for( uint value = 1; value < 14; ++value )
					m_cards[ ( suit - 1 ) * 13 + value - 1 ] = Card( (Card::Suit)suit, (Card::Value)value );
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