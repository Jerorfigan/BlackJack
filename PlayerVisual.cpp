#include "stdafx.h"

#include "Globals.h"
#include "PlayerVisual.h"
#include "ServiceProvider.h"

namespace BlackJack
{
	/***************/
	/* Static Data */
	/***************/
	using namespace GameUtilities;
	PlayerVisual::PlayerData    PlayerVisual::m_playerData[ 4 ] =
									{
										{ Point2D( 1084, 350 ), Point2D( 1104, 500 ) },
										{ Point2D( 788, 350 ), Point2D( 808, 500 ) },
										{ Point2D( 492, 350 ), Point2D( 512, 500 ) },
										{ Point2D( 196, 350 ), Point2D( 216, 500 ) }
									};
	using namespace BlackJack;

	/****************/
	/* Constructors */
	/****************/
	PlayerVisual::PlayerVisual( uint playerIndex ) : m_playerIndex( playerIndex ), 
		m_playerHUD( m_playerData[ playerIndex ].m_firstHandPosition )
	{
	}

	/***********/
	/* Methods */
	/***********/
	
	/////////////
	// AddCard //
	/////////////
	void 
	PlayerVisual::AddCard( Card card, uint handIndex )
	{
		// Check to see if we need to create the first hand
		if( m_handVisuals.size() == 0 )
		{
			m_handVisuals.push_back( new HandVisual( m_playerData[ m_playerIndex ].m_firstHandPosition ) );
		}

		m_handVisuals[ handIndex ]->AddCard( card );
	}

	////////////
	// AddBet //
	////////////
	void    
	PlayerVisual::AddBet( uint amt, uint betIndex )
	{
		if( betIndex == 0 )
		{
			if( m_betVisuals.size() == 0 )
			{
				m_betVisuals.push_back( new PlayerBetVisual( m_playerData[ m_playerIndex ].m_betPosition, amt ) );
			}
			else
			{
				m_betVisuals[0]->SetAmount( amt );
			}
		}
		else
		{
			if( m_betVisuals.size() == 1 )
			{
				m_betVisuals[0]->SetPosition( m_playerData[ m_playerIndex ].m_betPosition + Point2D( 60, 0 ) );
				m_betVisuals.push_back( new PlayerBetVisual( m_playerData[ m_playerIndex ].m_betPosition + Point2D( -60, 0 ), amt ) );
			}
			else
			{
				m_betVisuals[1]->SetAmount( amt );
			}
		}
	}

	///////////
	// Split //
	///////////
	void 
	PlayerVisual::Split( uint handIndex )
	{
		// Create the new hand
		m_handVisuals.push_back( new HandVisual( m_playerData[ m_playerIndex ].m_firstHandPosition + -1 * HandVisual::m_splitOffset, true ) );

		// Add the split card to it
		m_handVisuals[ m_handVisuals.size() - 1 ]->AddSplitCard( 
			m_handVisuals[ handIndex ]->SplitHand() );
	}

	///////////////
	// ClearBets //
	///////////////
	void    
	PlayerVisual::ClearBets()
	{
		m_betVisuals.clear();
	}

	////////////
	// Update //
	////////////
	void 
	PlayerVisual::Update()
	{
		// Update all the hands
		for( HandVisualList::iterator handVisualItr = m_handVisuals.begin();
			 handVisualItr != m_handVisuals.end(); ++handVisualItr )
		{
			(*handVisualItr)->Update();
		}
	}

	//////////
	// Draw //
	//////////
	void 
	PlayerVisual::Draw()
	{
		// Draw all the hands
		for( HandVisualList::iterator handVisualItr = m_handVisuals.begin();
			 handVisualItr != m_handVisuals.end(); ++handVisualItr )
		{
			(*handVisualItr)->Draw();
		}

		// Draw the bet sprites
		for( BetVisualList::iterator betVisItr = m_betVisuals.begin();
			 betVisItr != m_betVisuals.end(); ++betVisItr )
		{
			(*betVisItr)->Draw();
		}
	}

	//////////////////
	// DrawTextInfo //
	//////////////////
	void 
	PlayerVisual::DrawHUD()
	{
		m_playerHUD.Draw();
		
		// Draw the bet text
		for( BetVisualList::iterator betVisItr = m_betVisuals.begin();
			 betVisItr != m_betVisuals.end(); ++betVisItr )
		{
			(*betVisItr)->DrawText();
		}
	}

	///////////
	// Reset //
	///////////
	void    
	PlayerVisual::Reset()
	{
		m_handVisuals.clear();
		m_betVisuals.clear();
	}

	////////////////
	// Destructor //
	////////////////
	PlayerVisual::~PlayerVisual()
	{
		// Free hand visual objects
		for( HandVisualList::iterator handVisualItr = m_handVisuals.begin();
			 handVisualItr != m_handVisuals.end(); ++handVisualItr )
		{
			delete *handVisualItr;
		}

		// Free bet visual objects
		for( BetVisualList::iterator betVisualItr = m_betVisuals.begin();
			 betVisualItr != m_betVisuals.end(); ++betVisualItr )
		{
			delete *betVisualItr;
		}
	}

}