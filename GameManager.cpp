#include "stdafx.h"

#include "GameManager.h"
#include "GameError.h"
#include "GameInput.h"
#include "GameVisualizer.h"
#include "AIPlayer.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	GameManager::GameManager()
	{
		if( m_pGameManager )
			throw GameError( "[GameManager::GameManager]: Attempt to instantiate multiple instances of singleton class GameManager." );

		m_pGameManager = this;

		/* Create game visualizer and input singletons */
		GameInput::Create();
		GameVisualizer::Create();

		/* Setup default game settings. */

		PlayerConfiguration playerConfig;

		// Player defaults: 1 user controlled and 3 AI players.
		m_gameConfig.NumPlayers = 4;
		playerConfig.IsAIPlayer = false;
		m_gameConfig.PlayerConfigs.push_back( playerConfig );
		playerConfig.IsAIPlayer = true;
		m_gameConfig.PlayerConfigs.push_back( playerConfig );
		m_gameConfig.PlayerConfigs.push_back( playerConfig );
		m_gameConfig.PlayerConfigs.push_back( playerConfig );

		// Dealer defaults.
		m_gameConfig.DealerConfig.HitOnSoftSeventeen = false;

		// Misc defaults.
		m_gameConfig.AllowSplit = true;
		m_gameConfig.AllowSurrender = false;

		// Add some AI players.
		m_players.push_back( new AIPlayer() );
		m_players.push_back( new AIPlayer() );
		m_players.push_back( new AIPlayer() );
		m_players.push_back( new AIPlayer() );

		// Visualize game board
		GameVisualizer::VisualizationData visData;
		GameVisuals()->Visualize( GameVisualizer::GameBoard, visData );
	}

	/***********/
	/* Methods */
	/***********/

	////////////
	// Update //
	////////////
	void    
	GameManager::Update()
	{
		m_taskManager.PerformTask();

		GameVisuals()->Update();
	}

	///////////
	// Reset //
	///////////
	void    
	GameManager::Reset()
	{
		m_taskManager.Reset();
	}

	/**************/
	/* Destructor */
	/**************/
	GameManager::~GameManager()
	{
		// Free memory allocated for the players
		for( PlayerList::iterator playerItr = m_players.begin(); 
			 playerItr != m_players.end(); ++playerItr )
		{
			 delete *playerItr;
		}
	}

	/******************/
	/* Static methods */
	/******************/
	
	////////////
	// Create //
	////////////
	void			   
	GameManager::Create()
	{
		new GameManager();
	}

	/////////////
	// Destroy //
	/////////////
	void			   
	GameManager::Destroy()
	{
		// Destroy game input and visualizer singletons.
		GameInput::Destroy();
		GameVisualizer::Destroy();

		delete m_pGameManager;
		m_pGameManager = NULL;
	}

	/***************/
	/* Static data */
	/***************/
	GameManager*    GameManager::m_pGameManager = NULL;
}