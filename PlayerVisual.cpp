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
										{ Point2D( 1084, 450 ) },
										{ Point2D( 788, 450 ) },
										{ Point2D( 492, 450 ) },
										{ Point2D( 196, 450 ) }
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
	}

	//////////////////
	// DrawTextInfo //
	//////////////////
	void 
	PlayerVisual::DrawHUD()
	{
		m_playerHUD.Draw();
	}

	///////////
	// Reset //
	///////////
	void    
	PlayerVisual::Reset()
	{
		m_handVisuals.clear();
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
	}

}