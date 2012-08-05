#include "stdafx.h"

#include "PlayerVisual.h"

namespace BlackJack
{
	/***************/
	/* Static Data */
	/***************/
	using namespace GameUtilities;
	PlayerVisual::PlayerData    PlayerVisual::m_playerData[ 4 ] =
									{
										{ Point2D( 1024, 600 ), Point2D( 1124, 600 ) },
										{ Point2D( 768, 600 ), Point2D( 868, 600 ) },
										{ Point2D( 512, 600 ), Point2D( 612, 600 ) },
										{ Point2D( 256, 600 ), Point2D( 356, 600 ) }
									};
	using namespace BlackJack;

	/****************/
	/* Constructors */
	/****************/
	PlayerVisual::PlayerVisual( uint playerIndex ) : m_playerIndex( playerIndex )
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
		m_handVisuals.push_back( new HandVisual( m_playerData[ m_playerIndex ].m_secondHandPosition ) );

		// Add the split card to it
		m_handVisuals[ m_handVisuals.size() - 1 ]->AddSplitCard( 
			m_handVisuals[ handIndex ]->SplitHand() );
	}

	////////////
	// Update //
	////////////
	void 
	PlayerVisual::Update( float elapsedTime )
	{
		// Update all the hands
		for( HandVisualList::iterator handVisualItr = m_handVisuals.begin();
			 handVisualItr != m_handVisuals.end(); ++handVisualItr )
		{
			(*handVisualItr)->Update( elapsedTime );
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