#pragma once

#include <map>
#include <Windows.h>

#include "Globals.h"
#include "Card.h"
#include "..\GameUtilities\Point2D.h"
#include "Visualization.h"

namespace BlackJack
{

	class CardVisual
	{
		/***************/
		/* Static Data */
		/***************/
	private:
		static GameUtilities::Point2D			  m_cardDeckPosition;

		/****************/
		/* Constructors */
		/****************/
	public:
		CardVisual( Card card, GameUtilities::Point2D position, uint cardNum );

		/***********/
		/* Methods */
		/***********/
	public:
		void    ChangePosition( GameUtilities::Point2D newPosition );
		void    Flip();

		void    Update();
		void    Draw();

		~CardVisual();

	private:
		void GetFlipTransforms( Transform &transform1, Transform &transform2 );

		/********/
		/* Data */
		/********/
	private:
		Visualization             *m_pVisualization;
		Card                      m_card;
		GameUtilities::Point2D    m_targetPosition;
		uint                      m_cardNum;              
	};

}