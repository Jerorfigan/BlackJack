#pragma once

#include "Globals.h"
#include "Card.h"

namespace BlackJack
{

	class Player
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum PlayerStatus { Hit, Double, Split, Stand, Surrender, Busted };

		/**************************/
		/* Pure virtual functions */
		/**************************/
	public:
		virtual void AddCardToHand( const Card &card, uint handIndex = 0 ) = 0;
		virtual void DoubleBet( uint handIndex ) = 0;

		virtual PlayerStatus GetStatus( uint handIndex ) = 0;
		virtual uint GetCurrentBet( uint handIndex ) = 0;
		virtual uint GetNumHands() = 0;
	};

}