#include "stdafx.h"

#include "GameInput.h"

#include "UserPlayer.h"

namespace BlackJack
{

	/*******************/
	/* Virtual methods */
	/*******************/

	///////////////////////
	// CreateStartingBet //
	///////////////////////
	bool    
	UserPlayer::CreateStartingBet()
	{
		GameInput::InputData inpData;

		inpData.prompt = "How much would you like to bet?";

		inpData.choices.push_back( "$1" );
		if( m_chips >= 10 )
			inpData.choices.push_back( "$10" );
		if( m_chips >= 50 )
			inpData.choices.push_back( "$50" );
		if( m_chips >= 100 )
			inpData.choices.push_back( "$100" );
		if( m_chips >= 500 )
			inpData.choices.push_back( "$500" );
		if( m_chips >= 1000 )
			inpData.choices.push_back( "$1000" );

		inpData.hotKeys.push_back( '1' );
		if( m_chips >= 10 )
			inpData.hotKeys.push_back( '2' );
		if( m_chips >= 50 )
			inpData.hotKeys.push_back( '3' );
		if( m_chips >= 100 )
			inpData.hotKeys.push_back( '4' );
		if( m_chips >= 500 )
			inpData.hotKeys.push_back( '5' );
		if( m_chips >= 1000 )
			inpData.hotKeys.push_back( '6' );

		bool inputReceived = GameInp()->GetInput( m_playerNum, GameInput::TextPrompt, inpData );

		if( inputReceived )
		{
			if( inpData.selectedChoice == "$1" )
				m_currentBets[0] += 1, m_chips -= 1;
			else if( inpData.selectedChoice == "$10" )
				m_currentBets[0] += 10, m_chips -= 10;
			else if( inpData.selectedChoice == "$50" )
				m_currentBets[0] += 50, m_chips -= 50;
			else if( inpData.selectedChoice == "$100" )
				m_currentBets[0] += 100, m_chips -= 100;
			else if( inpData.selectedChoice == "$500" )
				m_currentBets[0] += 500, m_chips -= 500;
			else 
				m_currentBets[0] += 1000, m_chips -= 1000;
		}

		return inputReceived;
	}

	//////////////////////
	// SelectHandStatus //
	//////////////////////
	bool    
	UserPlayer::SelectHandStatus( uint handIndex )
	{
		GameInput::InputData inpData;

		inpData.prompt = "What would you like to do?";

		inpData.choices.push_back( "Hit" );
		if( CanDouble( handIndex ) )
			inpData.choices.push_back( "Double" );
		if( CanSplit() ) 
			inpData.choices.push_back( "Split" );
		inpData.choices.push_back( "Stand" );
		if( m_hands[ handIndex ].CanSurrender() ) 
			inpData.choices.push_back( "Surrender" );

		inpData.hotKeys.push_back( 'h' );
		if( CanDouble( handIndex ) )
			inpData.hotKeys.push_back( 'd' );
		if( CanSplit() ) 
			inpData.hotKeys.push_back( 's' );
		inpData.hotKeys.push_back( 'a' );
		if( m_hands[ handIndex ].CanSurrender() ) 
			inpData.hotKeys.push_back( 'f' );

		bool inputReceived = GameInp()->GetInput( m_playerNum, GameInput::TextPrompt, inpData );

		if( inputReceived )
		{
			if( inpData.selectedChoice == "Hit" )
				m_handStatuses[ handIndex ] = Hit;
			else if( inpData.selectedChoice == "Double" )
				m_handStatuses[ handIndex ] = Double;
			else if( inpData.selectedChoice == "Split" )
				m_handStatuses[ handIndex ] = Split;
			else if( inpData.selectedChoice == "Stand" )
				m_handStatuses[ handIndex ] = Stand;
			else
				m_handStatuses[ handIndex ] = Surrender;
		}

		return inputReceived;
	}

	///////////////
	// PlayAgain //
	///////////////
	bool    
	UserPlayer::PlayAgain( bool &again )
	{
		GameInput::InputData inpData;

		inpData.prompt = "Play again?";

		inpData.choices.push_back( "Yes" );
		inpData.choices.push_back( "No" );

		inpData.hotKeys.push_back( 'y' );
		inpData.hotKeys.push_back( 'n' );

		bool inputReceived = GameInp()->GetInput( m_playerNum, GameInput::TextPrompt, inpData );

		if( inputReceived )
		{
			if( inpData.selectedChoice == "Yes" )
				again = true;
			else
				again = false;
		}

		return inputReceived;
	}
}