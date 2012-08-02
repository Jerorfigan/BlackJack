#include "stdafx.h"

#include "Hand.h"
#include "GameManager.h"

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

	//////////////
	// CanSplit //
	//////////////
	bool 
	Hand::CanSplit() const
	{
		// Can split if hand has 2 cards of equal value (all face cards count as 10)
		return ( GameMgr()->GetGameConfiguration().AllowSplit && m_cards.size() == 2 && 
			( m_cards[0].m_value == m_cards[1].m_value || 
			( ( m_cards[0].m_value == Card::King || m_cards[0].m_value == Card::Queen || m_cards[0].m_value == Card::Jack || m_cards[0].m_value == Card::Ten ) && 
			( m_cards[1].m_value == Card::King || m_cards[1].m_value == Card::Queen || m_cards[1].m_value == Card::Jack || m_cards[1].m_value == Card::Ten ) ) ) );
	}

	//////////////////
	// CanSurrender //
	//////////////////
	bool 
	Hand::CanSurrender() const
	{
		// Can surrender if hand has 2 cards
		return ( GameMgr()->GetGameConfiguration().AllowSurrender && m_cards.size() == 2 );
	}

}