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
		uint GetNumCards() const;

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