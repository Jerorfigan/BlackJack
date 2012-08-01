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
		virtual void SplitHand( uint handIndex ) = 0;
		virtual void AddChips( uint chips ) = 0;
		virtual void SubtractChips( uint chips ) = 0;

		virtual PlayerStatus GetStatus( uint handIndex ) const = 0;
		virtual uint GetCurrentBet( uint handIndex ) const = 0;
		virtual uint GetNumHands() const = 0;
		virtual uint GetHandValue( uint handIndex ) const = 0;
		virtual bool CanPlay( uint handIndex ) const = 0;
		virtual bool HasBlackJack( uint handIndex ) const = 0;
	};

}