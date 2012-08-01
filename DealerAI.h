#pragma once

#include "Globals.h"
#include "Card.h"

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

		/**************/
		/* Destructor */
		/**************/
	public:
		~DealerAI();
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
		return 0;
	}
}