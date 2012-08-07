#pragma once

#include "Globals.h"
#include "..\GameUtilities\Point2D.h"
#include "..\GameUtilities\IGraphicsProvider.h"

namespace BlackJack
{

	class PlayerBetVisual
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		PlayerBetVisual( GameUtilities::Point2D position, uint amt );

		/***********/
		/* Methods */
		/***********/
	public:
		void SetPosition( GameUtilities::Point2D position );
		void SetAmount( uint amt );
		void Draw();
		void DrawText();

		~PlayerBetVisual();

		/********/
		/* Data */
		/********/
	private:
		GameUtilities::IGraphicsProvider::TextCollectionID      m_betTextID;
		GameUtilities::IGraphicsProvider::SpriteCollectionID    m_betVisualID;
	};

}