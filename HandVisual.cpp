#include "stdafx.h"

#include "HandVisual.h"

namespace BlackJack
{

	/***************/
	/* Static Data */
	/***************/
	GameUtilities::Point2D    HandVisual::m_cardOffset( 20.0f, -20.0f );

	/****************/
	/* Constructors */
	/****************/
	HandVisual::HandVisual( GameUtilities::Point2D position ) : m_position( position )
	{
	}

	/***********/
	/* Methods */
	/***********/
	
	/////////////
	// AddCard //
	/////////////
	void           
	HandVisual::AddCard( Card card )
	{
		GameUtilities::Point2D offset = static_cast< float >( m_cardVisuals.size() ) * m_cardOffset;

		m_cardVisuals.push_back( new CardVisual( card, m_position + offset, m_cardVisuals.size() + 1 ) );
	}

	//////////////////
	// AddSplitCard //
	//////////////////
	void           
	HandVisual::AddSplitCard( CardVisual *splitCardVisual )
	{
		splitCardVisual->ChangePosition( m_position );

		m_cardVisuals.push_back( splitCardVisual );
	}

	///////////////
	// SplitHand //
	///////////////
	CardVisual*    
	HandVisual::SplitHand()
	{
		CardVisual *pCardVisual = m_cardVisuals[ 1 ];
		m_cardVisuals.pop_back();
		return pCardVisual;
	}

	////////////
	// Update //
	////////////
	void           
	HandVisual::Update()
	{
		// Update card visuals
		for( CardVisualList::iterator cardVisualItr = m_cardVisuals.begin(); 
			 cardVisualItr != m_cardVisuals.end(); ++cardVisualItr )
		{
			(*cardVisualItr)->Update();
		}
	}

	//////////
	// Draw //
	//////////
	void           
	HandVisual::Draw()
	{
		// Draw card visuals
		for( CardVisualList::iterator cardVisualItr = m_cardVisuals.begin(); 
			 cardVisualItr != m_cardVisuals.end(); ++cardVisualItr )
		{
			(*cardVisualItr)->Draw();
		}
	}

	////////////////
	// HandVisual //
	////////////////
	HandVisual::~HandVisual()
	{
		// Free card visual objects
		for( CardVisualList::iterator cardVisualItr = m_cardVisuals.begin(); 
			 cardVisualItr != m_cardVisuals.end(); ++cardVisualItr )
		{
			delete *cardVisualItr;
		}
	}
}