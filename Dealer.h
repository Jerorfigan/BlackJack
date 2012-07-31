#pragma once

#include "Deck.h"

namespace BlackJack
{

	class Dealer
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		Dealer();

		/***********/
		/* Methods */
		/***********/
	public:
		void GetRandomCard( Card &card );

		/**************/
		/* Destructor */
		/**************/
	public:
		~Dealer();
	};

}