#include "stdafx.h"

#include "Dealer.h"
#include "GameError.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/

	/* Once the number of cards in the deck drops below reshufflePoint percent of its total capacity,
		the deck will be reshuffled. */
	Dealer::Dealer( uint numDecks, uint reshufflePoint ) : m_reshufflePoint( reshufflePoint ) 
	{
		// Create a card index list that contains indexes for all the cards in the deck (0-51)
		CardIndexList cardIndexList;
		for( uint cardIndex = 0; cardIndex < 52; ++cardIndex )
			cardIndexList.push_back( cardIndex );

		// Add numDecks copies of this card index list to m_drawCards
		for( uint i = 0; i < numDecks; ++i );
			m_drawCards.push_back( cardIndexList );

		// Add numDecks copies of an empty card index list to m_tableCards and m_deadCards
		CardIndexList emptyList;
		for( uint i = 0; i < numDecks; ++i );
		{
			m_tableCards.push_back( emptyList );
			m_deadCards.push_back( emptyList );
		}
	}

	/***********/
	/* Methods */
	/***********/

	///////////////////
	// GetRandomCard //
	///////////////////
	void 
	Dealer::GetRandomCard( Card &card )
	{
		// Safety check: make sure there is at least one card to deal
		uint cardsRemaining = 0;
		for( CardIndexListByDeck::iterator cardIndexListItr = m_drawCards.begin(); 
			 cardIndexListItr != m_drawCards.end(); ++cardIndexListItr )
			 cardsRemaining += cardIndexListItr->size();
		if( cardsRemaining == 0 )
			throw GameError( "[Dealer::GetRandomCard]: No cards to deal. " );

		uint deckIndex;
		uint selectedEntryNum = 9999;

		do
		{
			// Select a random deck to draw the card from
			deckIndex = RandomBetween( 0, m_drawCards.size() - 1 );

			// Select a random entry from the draw card index list for this deck
			// if it has at least entry present.
			if( m_drawCards[ deckIndex ].size() > 0 )
			{
				selectedEntryNum = RandomBetween( 1, m_drawCards[ deckIndex ].size() );
			}
		}
		while( selectedEntryNum == 9999 );
		
		// Iterate through the list of draw card indexes for this deck to find the selected entry
		uint cardIndex;
		uint counter = 0;
		for( CardIndexList::iterator cardIndexItr = m_drawCards[ deckIndex ].begin(); 
			 cardIndexItr != m_drawCards[ deckIndex ].end(); ++cardIndexItr )
		{
			if( ++counter == selectedEntryNum )
			{
				cardIndex = *cardIndexItr;
				// Add this card index to the list of table card indexes for this deck
				m_tableCards[ deckIndex ].push_back( cardIndex );
				// Remove this card index from the list of draw card indexes for this deck
				m_drawCards[ deckIndex ].erase( cardIndexItr );
				break;
			}
		}

		// Just copy over the suit/value. The calling code will be responsible for setting the orientation.
		card.m_suit = m_deck[ cardIndex ].m_suit;
		card.m_value = m_deck[ cardIndex ].m_value;

		// Check to see if we need to reshuffle
		if( --cardsRemaining < m_drawCards.size() * 52 * ( m_reshufflePoint / 100.0f ) )
		{
			Reshuffle();
		}
	}

	///////////////
	// KillCards //
	///////////////
	void 
	Dealer::KillCards()
	{
		/* Move all table card indexes into the dead card index lists */

		for( CardIndexListByDeck::iterator tableCardIndexListItr = m_tableCards.begin(), deadCardIndexListItr = m_deadCards.begin();
			 tableCardIndexListItr != m_tableCards.end(); ++tableCardIndexListItr, ++deadCardIndexListItr )
		{
			 for( CardIndexList::iterator tableCardIndexItr = tableCardIndexListItr->begin(); 
				  tableCardIndexItr != tableCardIndexListItr->end(); ++tableCardIndexItr )
				  deadCardIndexListItr->push_back( *tableCardIndexItr );
			 tableCardIndexListItr->clear();
		}
	}

	///////////////
	// Reshuffle //
	///////////////
	void 
	Dealer::Reshuffle()
	{
		/* Move all dead cards indexes back into the draw card index lists. */

		for( CardIndexListByDeck::iterator deadCardIndexListItr = m_deadCards.begin(), drawCardIndexListItr = m_drawCards.begin();
			 deadCardIndexListItr != m_deadCards.end(); ++deadCardIndexListItr, ++drawCardIndexListItr )
		{
			 for( CardIndexList::iterator deadCardIndexItr = deadCardIndexListItr->begin(); 
				  deadCardIndexItr != deadCardIndexListItr->end(); ++deadCardIndexItr )
				  drawCardIndexListItr->push_back( *deadCardIndexItr );
			 deadCardIndexListItr->clear();
		}
	}

}