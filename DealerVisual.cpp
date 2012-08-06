#include "stdafx.h"

#include "DealerVisual.h"

namespace BlackJack
{

	/***************/
	/* Static Data */
	/***************/
	const GameUtilities::Point2D    DealerVisual::m_holeCardPos( 540, 175 );
	const GameUtilities::Point2D    DealerVisual::m_dealerHandPos( 740, 175 );

	/****************/
	/* Constructors */
	/****************/
	DealerVisual::DealerVisual() : m_pHoleCard( NULL ), m_handVisual( m_dealerHandPos )
	{
	}

	/***********/
	/* Methods */
	/***********/
	
	/////////////
	// AddCard //
	/////////////
	void    
	DealerVisual::AddCard( Card card )
	{
		if( m_handVisual.GetCardCount() == 1 && m_pHoleCard == NULL )
		{
			m_pHoleCard = new CardVisual( card, m_holeCardPos, 1 );
		}
		else
		{
			m_handVisual.AddCard( card );
		}
	}

	////////////////////
	// RevealHoleCard //
	////////////////////
	void    
	DealerVisual::RevealHoleCard()
	{
		if( m_pHoleCard != NULL )
		{
			m_pHoleCard->Flip();
		}
	}
		
	////////////
	// Update //
	////////////
	void    
	DealerVisual::Update()
	{
		// Update hole card
		if( m_pHoleCard != NULL )
		{
			m_pHoleCard->Update();
		}

		// Update dealer hand
		m_handVisual.Update();
	}
	
	//////////
	// Draw //
	//////////
	void    
	DealerVisual::Draw()
	{
		// Draw hole card
		if( m_pHoleCard != NULL )
		{
			m_pHoleCard->Draw();
		}

		// Draw dealer hand
		m_handVisual.Draw();
	}

	////////////////
	// Destructor //
	////////////////
	DealerVisual::~DealerVisual()
	{
		// Free hole card visual
		delete m_pHoleCard;
	}

}