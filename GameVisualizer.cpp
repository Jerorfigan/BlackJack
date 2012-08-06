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
				m_gameBoardVisual.SetVisibility( true );
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
				m_dealerVisual.AddCard( data.DealerCard );
			}
			break;
		case DealerRevealHole:
			{
				m_dealerVisual.RevealHoleCard();
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
		case ShowPrompt:
			{
				// Unpack the selection/hotkey data which was sent as char** and char* respectively, due to 
				// union intolerance of STL types.
				std::vector< std::string > selections;
				for( uint index = 0; index < data.NumSelections; ++index )
					selections.push_back( data.Selections[ index ] );
				std::vector< char > hotkeys;
				for( uint index = 0; index < data.NumHotKeys; ++index )
					hotkeys.push_back( data.HotKeys[ index ] );

				m_playerPrompt.SetPrompt( data.PlayerNum, data.Prompt, selections, hotkeys );
				m_playerPrompt.DisplayPrompt();
			}
			break;
		case HidePrompt:
			{
				m_playerPrompt.HidePrompt();
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