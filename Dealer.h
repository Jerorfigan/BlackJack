#pragma once

#include <vector>
#include <list>

#include "Globals.h"
#include "Deck.h"

namespace BlackJack
{

	class Dealer
	{
		/***********/
		/* Typedef */
		/***********/
	private:
		typedef std::list< uint > CardIndexList;
		typedef std::vector< CardIndexList > CardIndexListByDeck;

		/****************/
		/* Constructors */
		/****************/
	public:
		/* Once the number of cards in the main deck drops below reshufflePoint percent of its total capacity,
		   the main deck will be reshuffled. */
		Dealer( uint numDecks = 1, uint reshufflePoint = 25 );

		/***********/
		/* Methods */
		/***********/
	public:
		void GetRandomCard( Card &card );
		/* All cards obtained from GetRandomCard are assumed to be on the table and in play until KillCards is called, 
		   at which point all cards dealt since last call to KillCards become dead cards that are eligible for reshuffle. */
		void KillCards();
		void Reshuffle();
		
		~Dealer() {};

		/********/
		/* Data */
		/********/
	private:
		Deck				   m_deck;
		CardIndexListByDeck    m_drawCards; // indexes of cards waiting to be drawn
		CardIndexListByDeck	   m_tableCards; // indexes of cards on the table
		CardIndexListByDeck    m_deadCards; // indexes of cards that have already been played 
		uint                   m_reshufflePoint;
	};

}