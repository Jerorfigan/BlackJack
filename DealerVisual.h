#pragma once

#include "Card.h"
#include "..\GameUtilities\Point2D.h"
#include "HandVisual.h"
#include "CardVisual.h"

namespace BlackJack
{

	class DealerVisual
	{
		/***************/
		/* Static Data */
		/***************/
	private:
		static const GameUtilities::Point2D    m_holeCardPos;
		static const GameUtilities::Point2D    m_dealerHandPos;

		/****************/
		/* Constructors */
		/****************/
	public:
		DealerVisual();

		/***********/
		/* Methods */
		/***********/
	public:
		void    AddCard( Card card );
		void    RevealHoleCard();
		
		void    Update();
		void    Draw();

		~DealerVisual();

		/********/
		/* Data */
		/********/
	private:
		CardVisual    *m_pHoleCard;
		HandVisual    m_handVisual;
	};

}