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
		Hand( uint handNum );
		Hand( const Card &card, uint handNum );

		/***********/
		/* Methods */
		/***********/
	public:
		void AddCard( const Card &card );
		Card RemoveTopCard();
		void Reset();

		/* Returns true if value is soft, false if hard. */
		bool GetValue( uint &value ) const;
		bool HasBlackJack() const;
		bool CanSplit() const;
		bool CanSurrender() const;
		uint GetNumCards() const;

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
		uint     m_handNum;
		bool     m_hasSplit;
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

	/////////////////
	// GetNumCards //
	/////////////////
	inline uint 
	Hand::GetNumCards() const
	{
		return m_cards.size();
	}

}