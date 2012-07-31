#pragma once

#include "TaskManager.h"
#include "GameConfiguration.h"

namespace BlackJack
{

	class GameManager
	{
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