#include "stdafx.h"

#include "GameVisualizer.h"
#include "GameError.h"
#include "ServiceProvider.h"
#include "GameManager.h"

namespace BlackJack
{
	/****************/
	/* Constructors */
	/****************/
	GameVisualizer::GameVisualizer()
	{
		if( m_pGameVisualizer )
			throw GameError( "[GameVisualizer::GameVisualizer]: Attempt to instantiate multiple instances of singleton GameVisualizer." );

		m_pGameVisualizer = this;

		// Create the player visual objects
		for( uint playerIndex = 0; playerIndex < GameMgr()->GetGameConfiguration().NumPlayers; ++playerIndex )
		{
			m_playerVisuals.push_back( new PlayerVisual( playerIndex ) );
		}
	}

	/***********/
	/* Methods */
	/***********/

	///////////////
	// Visualize //
	///////////////
	void
	GameVisualizer::Visualize( VisualizationType visType, const VisualizationData &data )
	{
		switch( visType )
		{
		case GameBoard:
			{
			}
			break;
		case PlayerXHandYMadeBetZ:
			{
			}
			break;
		case PlayerXHandYDealtCardZ:
			{
				m_playerVisuals[ data.PlayerNum - 1 ]->AddCard( data.PlayerCard, data.HandIndex );
			}
			break;
		case PlayerXHandYSplit:
			{
				m_playerVisuals[ data.PlayerNum - 1 ]->Split( data.HandIndex );
			}
			break;
		case PlayerXSurrender:
			{
			}
			break;
		case DealerDeltCardX:
			{
			}
			break;
		case DealerRevealHole:
			{
			}
			break;
		case PlayerXWonHandYWinningZ:
			{
			}
			break;
		case PlayerXPushedHandY:
			{
			}
			break;
		case PlayerXLostHandY: 
			{
			}
			break;
		case PlayerXAdjustChipsToY:
			{
			}
			break;
		}
	}

	///////////////////////////
	// VisualizationComplete //
	///////////////////////////
	bool 
	GameVisualizer::VisualizationsComplete()
	{
		bool allVisualizationsComplete = true;

		// Check all active visualizations: if any are not complete, return false. If all complete,
		// clear the active visualization list and return true.
		for( VisualizationList::iterator visualizationItr = m_activeVisualizations.begin();
			 visualizationItr != m_activeVisualizations.end(); ++visualizationItr )
		{
			if( !(*visualizationItr)->Complete() )
			{
				allVisualizationsComplete = false;
				break;
			}
		}

		if( allVisualizationsComplete )
		{
			m_activeVisualizations.clear();
		}

		return allVisualizationsComplete;
	}

	////////////
	// Update //
	////////////
	void GameVisualizer::Update()
	{
		// Update the player visuals
		for( PlayerVisualList::iterator playerVisualItr = m_playerVisuals.begin();
			 playerVisualItr != m_playerVisuals.end(); ++playerVisualItr )
		{
			(*playerVisualItr)->Update();
		}
	}

	//////////
	// Draw //
	//////////
	void                
	GameVisualizer::Draw()
	{
		ServProvider()->GetGraphicsProvider()->ClearBackbuffer();
		ServProvider()->GetGraphicsProvider()->BeginScene();
		ServProvider()->GetGraphicsProvider()->StartSpriteBatch();

		// Draw the player visuals
		for( PlayerVisualList::iterator playerVisualItr = m_playerVisuals.begin();
			 playerVisualItr != m_playerVisuals.end(); ++playerVisualItr )
		{
			(*playerVisualItr)->Draw();
		}

		ServProvider()->GetGraphicsProvider()->EndSpriteBatch();
		ServProvider()->GetGraphicsProvider()->EndScene();
		ServProvider()->GetGraphicsProvider()->Flip();
	}

	////////////////
	// Destructor //
	////////////////
	GameVisualizer::~GameVisualizer()
	{
		// Destroy the player visual objects
		for( PlayerVisualList::iterator playerVisualItr = m_playerVisuals.begin();
			 playerVisualItr != m_playerVisuals.end(); ++playerVisualItr )
		{
			delete *playerVisualItr;
		}
	}

	/******************/
	/* Static Methods */
	/******************/

	////////////
	// Create //
	////////////
	void 
	GameVisualizer::Create()
	{
		new GameVisualizer();
	}

	/////////////
	// Destroy //
	/////////////
	void 
	GameVisualizer::Destroy()
	{
		delete m_pGameVisualizer;
		m_pGameVisualizer = NULL;
	}

	/***************/
	/* Static Data */
	/***************/
	GameVisualizer*    GameVisualizer::m_pGameVisualizer = NULL;

}