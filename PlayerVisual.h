#pragma once

#include <vector>

#include "Globals.h"
#include "Card.h"
#include "HandVisual.h"
#include "..\GameUtilities\Point2D.h"

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
			GameUtilities::Point2D    m_secondHandPosition;
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
		void    Draw();

		~PlayerVisual();

		/********/
		/* Data */
		/********/
	private:
		 HandVisualList    m_handVisuals;
		 uint			   m_playerIndex;
	};

}