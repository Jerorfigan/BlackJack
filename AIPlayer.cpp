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

	bool    
	AIPlayer::SelectHandStatus( uint handIndex )
	{
		// AI likes to always live dangerous.
		m_handStatuses[ handIndex ] = Hit;

		return true;
	}

}