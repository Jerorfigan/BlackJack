#include "stdafx.h"

#include "Player.h"

namespace BlackJack
{
	/****************/
	/* Constructors */
	/****************/
	Player::Player() : m_chips( 0 )
	{

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

		m_hands.push_back( Hand( topCard ) );
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

}