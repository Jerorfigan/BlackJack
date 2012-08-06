#pragma once

#include "Globals.h"
#include "Card.h"
#include "Hand.h"

namespace BlackJack
{

	class DealerAI
	{
		/***************/
		/* Constructors */
		/***************/
	public:
		DealerAI();

		/***********/
		/* Methods */
		/***********/
	public:
		void AddCardToHand( const Card &card );
		void RevealHoleCard();

		uint GetNumCards() const;
		uint GetHandValue() const;
		bool HasBlackJack() const;
		bool CanHit() const;

		~DealerAI();

		/********/
		/* Data */
		/********/
	private:
		Hand    m_hand;
	};

	/***********/
	/* Inlines */
	/***********/
	
	/////////////////
	// GetNumCards //
	/////////////////
	inline uint 
	DealerAI::GetNumCards() const
	{
		return m_hand.GetNumCards();
	}

}