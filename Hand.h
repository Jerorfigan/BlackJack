#pragma once

#include <vector>

#include "Globals.h"
#include "Card.h"

namespace BlackJack
{

	class Hand
	{
		/************/
		/* Typedefs */
		/************/
	private:
		typedef std::vector< Card > Cards;

		/****************/
		/* Constructors */
		/****************/
	public:
		Hand();
		Hand( const Card &card );

		/***********/
		/* Methods */
		/***********/
	public:
		void AddCard( const Card &card );
		Card RemoveTopCard();

		/* Returns true if value is soft, false if hard. */
		bool GetValue( uint &value ) const;
		bool HasBlackJack() const;
		bool CanSplit() const;
		bool CanSurrender() const;

		/*************/
		/* Operators */
		/*************/
	public:
		Card& operator[]( uint cardIndex )
		{
			return m_cards[ cardIndex ];
		}

		/********/
		/* Data */
		/********/
	private:
		Cards    m_cards;
	};

	/***********/
	/* Inlines */
	/***********/
	
	//////////////////
	// HasBlackJack //
	//////////////////
	inline bool 
	Hand::HasBlackJack() const
	{
		if( m_cards.size() == 2 )
			if( m_cards[0].m_value == Card::Ace || m_cards[1].m_value == Card::Ace )
				if( ( m_cards[0].m_value == Card::Ten || m_cards[0].m_value == Card::Jack || m_cards[0].m_value == Card::Queen || m_cards[0].m_value == Card::King ) ||
					( m_cards[1].m_value == Card::Ten || m_cards[1].m_value == Card::Jack || m_cards[1].m_value == Card::Queen || m_cards[1].m_value == Card::King ) )
					return true;

		return false;
	}

}