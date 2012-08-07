#include "stdafx.h"

#include "GameVisualizer.h"
#include "GameError.h"
#include "ServiceProvider.h"
#include "GameManager.h"
#include "GameVisualizerInputStructs.h"

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
	GameVisualizer::Visualize( VisualizationType visType, void *pVisData )
	{
		switch( visType )
		{
		case GameBoard:
			{
				m_gameBoardVisual.SetVisibility( true );
			}
			break;
		case PlayerXHandYMadeBetZ:
			{
			}
			break;
		case PlayerXHandYDealtCardZ:
			{
				sPlayerXHandYDealtCardZ *pData = (sPlayerXHandYDealtCardZ*)pVisData;

				m_playerVisuals[ pData->playerIndex ]->AddCard( pData->card, pData->handIndex );
			}
			break;
		case PlayerXHandYSplit:
			{
				sPlayerXHandYSplit *pData = (sPlayerXHandYSplit*)pVisData;

				m_playerVisuals[ pData->playerIndex ]->Split( pData->handIndex );
			}
			break;
		case PlayerXSurrender:
			{
			}
			break;
		case DealerDeltCardX:
			{
				sDealerDeltCardX *pData = (sDealerDeltCardX*)pVisData;

				m_dealerVisual.AddCard( pData->card );
			}
			break;
		case DealerRevealHole:
			{
				m_dealerVisual.RevealHoleCard();
			}
			break;
		case PlayerXWonHandY:
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
		case PlayerXSetChipsToY:
			{
				sPlayerXSetChipsToY *pData = (sPlayerXSetChipsToY*)pVisData;

				m_playerVisuals[ pData->playerIndex ]->UpdatePlayerChips( pData->chips );
			}
			break;
		case ShowPlayerXPrompt:
			{
				sShowPlayerXPrompt *pData = (sShowPlayerXPrompt*)pVisData;

				m_playerPrompt.SetPrompt( pData->playerIndex + 1, pData->prompt, pData->selections, pData->hotkeys );
				m_playerPrompt.DisplayPrompt();
			}
			break;
		case HidePrompt:
			{
				m_playerPrompt.HidePrompt();
			}
			break;
		case PlayerXNameChanged:
			{
				sPlayerXNameChanged *pData = (sPlayerXNameChanged*)pVisData;

				m_playerVisuals[ pData->playerIndex ]->UpdatePlayerName( pData->name );
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
		// Update the dealer visual
		m_dealerVisual.Update();

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

		// Draw game board
		m_gameBoardVisual.Draw();

		// Draw the dealer visual
		m_dealerVisual.Draw();

		// Draw the player visuals
		for( PlayerVisualList::iterator playerVisualItr = m_playerVisuals.begin();
			 playerVisualItr != m_playerVisuals.end(); ++playerVisualItr )
		{
			(*playerVisualItr)->Draw();
		}

		// Draw player prompt background
		m_playerPrompt.DrawPromptBackground();

		ServProvider()->GetGraphicsProvider()->EndSpriteBatch();
		ServProvider()->GetGraphicsProvider()->StartSpriteBatch();
	
		// Draw player prompt text
		m_playerPrompt.DrawPromptText();

		// Draw the player info
		for( PlayerVisualList::iterator playerVisualItr = m_playerVisuals.begin();
			 playerVisualItr != m_playerVisuals.end(); ++playerVisualItr )
		{
			(*playerVisualItr)->DrawHUD();
		}

		ServProvider()->GetGraphicsProvider()->EndSpriteBatch();
		ServProvider()->GetGraphicsProvider()->EndScene();

		ServProvider()->GetGraphicsProvider()->Flip();
	}

	///////////
	// Reset //
	///////////
	void    
	GameVisualizer::Reset()
	{
		// Reset dealer
		m_dealerVisual.Reset();
	
		// ResetPlayers
		for( PlayerVisualList::iterator playerVisualItr = m_playerVisuals.begin();
			 playerVisualItr != m_playerVisuals.end(); ++playerVisualItr )
		{
			(*playerVisualItr)->Reset();
		}
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