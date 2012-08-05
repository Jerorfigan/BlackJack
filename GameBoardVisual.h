#pragma once

#include "..\GameUtilities\IGraphicsProvider.h"

namespace BlackJack
{

	class GameBoardVisual
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		GameBoardVisual();

		/***********/
		/* Methods */
		/***********/
	public:
		void SetVisibility( bool flag );

		void Update();
		void Draw();

		~GameBoardVisual();

		/********/
		/* Data */
		/********/
	private:
		GameUtilities::IGraphicsProvider::SpriteCollectionID    m_spriteCollectionID;
		bool    m_visible;
	};

}