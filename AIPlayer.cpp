#include "stdafx.h"

#include "AIPlayer.h"

namespace BlackJack
{

	/*******************/
	/* Virtual methods */
	/*******************/

	///////////////////////
	// CreateStartingBet //
	///////////////////////
	bool    
	AIPlayer::CreateStartingBet()
	{
		// Bet a random percentage between 15%-30% of total chips.
		float percentage = RandomBetween( 15, 30 ) / 100.0f;
		uint bet = static_cast< uint >( m_chips * percentage );
		m_chips -= bet;
		m_currentBets[ 0 ] = bet;

		return true;
	}

	//////////////////////
	// SelectHandStatus //
	//////////////////////
	bool    
	AIPlayer::SelectHandStatus( uint handIndex )
	{
		uint value;
		m_hands[ handIndex ].GetValue( value );

		// AI plays like dealer while taking advantage of splitting.
		if( m_hands[ handIndex ].CanSplit() )
		{
			m_handStatuses[ handIndex ] = Split;
		}
		else if( value < 17 )
		{
			m_handStatuses[ handIndex ] = Hit;
		}
		else
		{
			m_handStatuses[ handIndex ] = Stand;
		}

		return true;
	}

	///////////////
	// PlayAgain //
	///////////////
	bool    
	AIPlayer::PlayAgain( bool &again )
	{
		// AI doesnt influence player again outcome
		return true;
	}

}