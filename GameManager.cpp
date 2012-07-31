#include "stdafx.h"

#include "GameManager.h"
#include "GameError.h"

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
		delete m_pGameManager;
		m_pGameManager = NULL;
	}

	/***************/
	/* Static data */
	/***************/
	GameManager*    GameManager::m_pGameManager = NULL;
}