#include "stdafx.h"

#include "Hand.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	Hand::Hand()
	{
	}

	Hand::Hand( const Card &card )
	{
		m_cards.push_back( card );
	}
	
	/***********/
	/* Methods */
	/***********/

	/////////////
	// AddCard //
	/////////////
	void 
	Hand::AddCard( const Card &card )
	{
		m_cards.push_back( card );
	}

	///////////////////
	// RemoveTopCard //
	///////////////////
	Card
	Hand::RemoveTopCard()
	{
		Card topCard = m_cards.back();
		m_cards.pop_back();
		return topCard;
	}

	//////////////
	// GetValue // 
	//////////////
	bool  
	Hand::GetValue( uint &value ) const
	{
		bool soft = false;
		uint sum = 0;
		uint aceCount = 0;
		for( Cards::const_iterator cardItr = m_cards.begin();
			 cardItr != m_cards.end(); ++cardItr )
		{
			// Skip aces initially, we'll add in as 1 or 11 later
			if( cardItr->m_value == Card::Ace )
				++aceCount;
			else if( cardItr->m_value == Card::Jack || cardItr->m_value == Card::Queen || cardItr->m_value == Card::King )
				sum += 10;
			else
				sum += cardItr->m_value;
		}
		// Add in aces
		if( aceCount )
			if( sum + 11 + aceCount - 1 <= 21 )
				sum += 11 + aceCount - 1, soft = true;
			else 
				sum += aceCount;

		value = sum;

		return soft;
	}

}