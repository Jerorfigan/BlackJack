#include "stdafx.h"

#include "Player.h"

namespace BlackJack
{
	/****************/
	/* Constructors */
	/****************/
	Player::Player( uint playerNum ) : m_chips( 1000 ), m_playerNum( playerNum )
	{
		// Create the default hand
		m_hands.push_back( Hand( m_hands.size() + 1 ) );
		// Create the default bet placeholder
		m_currentBets.push_back( 0 );
		// Create the default handstatus placeholder
		m_handStatuses.push_back( Hit );
	}

	/***********/
	/* Methods */
	/***********/
	
	///////////////////
	// AddCardToHand //
	///////////////////
	void		  
	Player::AddCardToHand( const Card &card, uint handIndex )
	{
		m_hands[ handIndex ].AddCard( card );
	}

	//////////////
	// DoubleBet//
	//////////////
	void		  
	Player::DoubleBet( uint handIndex )
	{
		m_currentBets[ handIndex ] *= 2;
	}

	///////////////
	// SplitHand //
	///////////////
	void		  
	Player::SplitHand( uint handIndex )
	{
		Card topCard = m_hands[ handIndex ].RemoveTopCard();

		m_hands.push_back( Hand( topCard, m_hands.size() + 1 ) );
		// Copy bet from hand being split to new partial hand
		m_currentBets.push_back( m_currentBets[ handIndex ] );
		m_chips -= m_currentBets[ handIndex ];
		// Create the default handstatus placeholder for the new partial hand
		m_handStatuses.push_back( Hit );
	}

	//////////////
	// AddChips //
	//////////////
	void		  
	Player::AddChips( uint chips )
	{
		m_chips += chips;
	}

	///////////////////
	// SubtractChips //
	///////////////////
	void		  
	Player::SubtractChips( uint chips )
	{
		m_chips = m_chips - chips >= 0 ? m_chips - chips : 0; 
	}

	//////////////
	// ClearBet //
	//////////////
	void		  
	Player::ClearBet( uint handIndex )
	{
		m_currentBets[ handIndex ] = 0;
	}

	///////////
	// Reset //
	///////////
	void          
	Player::Reset()
	{
		// Clear hands & bets & handstatuses
		m_hands.clear();
		m_hands.push_back( Hand( m_hands.size() + 1 ) );
		m_currentBets.clear();
		m_currentBets.push_back( 0 );
		m_handStatuses.clear();
		m_handStatuses.push_back( Hit );
	}

}