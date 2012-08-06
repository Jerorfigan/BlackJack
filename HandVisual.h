#pragma once

#include <vector>

#include "Card.h"
#include "..\GameUtilities\Point2D.h"
#include "CardVisual.h"

namespace BlackJack
{

	class HandVisual
	{
		/************/
		/* Typedefs */
		/************/
	private:
		typedef std::vector< CardVisual* > CardVisualList;

		/***************/
		/* Static Data */
		/***************/
	private:
		static GameUtilities::Point2D    m_cardOffset;

		/****************/
		/* Constructors */
		/****************/
	public:
		HandVisual( GameUtilities::Point2D position );

		/***********/
		/* Methods */
		/***********/
	public:
		void           AddCard( Card card );
		void           AddSplitCard( CardVisual *splitCardVisual );
		CardVisual*    SplitHand();

		void           Update();
		void           Draw();

		uint           GetCardCount();

		~HandVisual();

		/********/
		/* Data */
		/********/
	private:
		CardVisualList            m_cardVisuals;
		GameUtilities::Point2D    m_position;
	};

	/**********/
	/* Inline */
	/**********/

	//////////////////
	// GetCardCount //
	//////////////////
	inline uint           
	HandVisual::GetCardCount()
	{
		return m_cardVisuals.size();
	}

}