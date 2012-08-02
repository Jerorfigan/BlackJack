#include "stdafx.h"

#include "DealerAI.h"
#include "GameManager.h"

namespace BlackJack
{

	/***************/
	/* Constructors */
	/***************/
	DealerAI::DealerAI()
	{
	}

	/***********/
	/* Methods */
	/***********/

	///////////////////
	// AddCardToHand //
	///////////////////
	void 
	DealerAI::AddCardToHand( const Card &card )
	{
		m_hand.AddCard( card );
	}

	////////////////////
	// RevealHoleCard //
	////////////////////
	void 
	DealerAI::RevealHoleCard()
	{
		m_hand[1].m_orientation = Card::FaceUp;
	}

	//////////////////
	// GetHandValue //
	//////////////////
	uint 
	DealerAI::GetHandValue() const
	{
		uint value;
		m_hand.GetValue( value ); 
		return value;
	}

	//////////////////
	// HasBlackJack //
	//////////////////
	bool 
	DealerAI::HasBlackJack() const
	{
		return m_hand.HasBlackJack();
	}

	////////////
	// CanHit //
	////////////
	bool 
	DealerAI::CanHit() const
	{
		uint value;
		bool soft = m_hand.GetValue( value ); 

		return value <= 16 || ( value == 17 && soft && GameMgr()->GetGameConfiguration().DealerConfig.HitOnSoftSeventeen );
	}

	////////////////
	// Destructor //
	////////////////
	DealerAI::~DealerAI()
	{

	}

}