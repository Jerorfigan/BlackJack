#pragma once

#include <vector>

#include "TaskManager.h"
#include "GameConfiguration.h"
#include "Player.h"
#include "Dealer.h"
#include "DealerAI.h"

namespace BlackJack
{

	class GameManager
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::vector< Player* > PlayerList;

		/****************/
		/* Constructors */
		/****************/
	public:
		GameManager();

		/***********/
		/* Methods */
		/***********/
	public:
		void						Update();
		void						Reset();
		void					    SetGameConfiguration( const GameConfiguration &gameConfig );
		const GameConfiguration&    GetGameConfiguration() const;
		PlayerList&                 GetPlayerList();
		Dealer&                     GetDealer();
		DealerAI&                   GetDealerAI();

		/**************/
		/* Destructor */
		/**************/
	public:
		~GameManager();

		/********/
		/* Data */
		/********/
	private:
		GameConfiguration     m_gameConfig;
		TaskManager           m_taskManager;
		PlayerList            m_players;
		Dealer                m_dealer;
		DealerAI			  m_dealerAI;

		/******************/
		/* Static methods */
		/******************/
	public:
		static void			   Create();
		static void			   Destroy();
		static GameManager*    GetGameManager();

		/***************/
		/* Static data */
		/***************/
	private:
		static GameManager*    m_pGameManager;
	};

	/***********/
	/* Inlines */
	/***********/

	//////////////////////////
	// SetGameConfiguration //
	//////////////////////////
	inline void					    
	GameManager::SetGameConfiguration( const GameConfiguration &gameConfig )
	{
		m_gameConfig = gameConfig;
	}

	//////////////////////////
	// GetGameConfiguration //
	//////////////////////////
	inline const GameConfiguration& 
	GameManager::GetGameConfiguration() const
	{
		return m_gameConfig;
	}

	///////////////////
	// GetPlayerList //
	///////////////////
	inline GameManager::PlayerList&                 
	GameManager::GetPlayerList()
	{
		return m_players;
	}

	///////////////
	// GetDealer //
	///////////////
	inline Dealer&                     
	GameManager::GetDealer()
	{
		return m_dealer;
	}

	/////////////////
	// GetDealerAI //
	/////////////////
	inline DealerAI&                   
	GameManager::GetDealerAI()
	{
		return m_dealerAI;
	}

	/******************/
	/* Static inlines */
	/******************/

	inline GameManager*    
	GameManager::GetGameManager()
	{
		return m_pGameManager;
	}

	/* Global abbreviated wrapper for GameManager::GetGameManager */ 
	inline GameManager*
	GameMgr()
	{
		return GameManager::GetGameManager();
	}

}