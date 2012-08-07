#pragma once

#include <vector>

#include "Globals.h"
#include "Card.h"
#include "HandVisual.h"
#include "PlayerHUD.h"

namespace BlackJack
{

	class PlayerVisual
	{
		/********************/
		/* Internal Classes */
		/********************/
	private:
		struct PlayerData
		{
			GameUtilities::Point2D    m_firstHandPosition;
		};

		/************/
		/* Typedefs */
		/************/
	private:
		typedef std::vector< HandVisual* > HandVisualList;

		/***************/
		/* Static Data */
		/***************/
	private:
		static PlayerData    m_playerData[ 4 ];

		/****************/
		/* Constructors */
		/****************/
	public:
		PlayerVisual( uint playerIndex );

		/***********/
		/* Methods */
		/***********/
	public:
		void    AddCard( Card card, uint handIndex );
		void    Split( uint handIndex );

		void    Update();
		void    UpdatePlayerName( std::string name );
		void    UpdatePlayerChips( uint chips );
		void    Draw();
		void    DrawHUD();

		void    Reset();

		~PlayerVisual();

		/********/
		/* Data */
		/********/
	private:
		 HandVisualList    m_handVisuals;
		 uint			   m_playerIndex;
		 PlayerHUD         m_playerHUD;
	};

	/***********/
	/* Inlines */
	/***********/
	
	//////////////////////
	// UpdatePlayerName //
	//////////////////////
	inline void    
	PlayerVisual::UpdatePlayerName( std::string name )
	{
		m_playerHUD.SetName( name );
	}

	///////////////////////
	// UpdatePlayerChips //
	///////////////////////
	inline void    
	PlayerVisual::UpdatePlayerChips( uint chips )
	{
		m_playerHUD.SetChips( chips );
	}

}