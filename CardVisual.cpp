#include "stdafx.h"

#include "CardVisual.h"
#include "DynamicImage.h"
#include "GameVisualizer.h"

namespace BlackJack
{
	/***************/
	/* Static Data */
	/***************/
	GameUtilities::Point2D    CardVisual::m_cardDeckPosition( 100, 100 );

	/****************/
	/* Constructors */
	/****************/
	CardVisual::CardVisual( Card card, GameUtilities::Point2D position, uint cardNum ) :
		m_card( card ), m_targetPosition( position ), m_cardNum( cardNum )
	{
		/* Create the card being dealt to player visualization */

		// First create the dynamic image definition
		DynamicImage::DynamicImageDef dynamicImgDef;
		Transform transform;
		transform.m_imagePath = "Data\\CardSheet.png";
		transform.m_subrect.left = ((uint)m_card.m_value - 1) * 111 + ((uint)m_card.m_value - 1) * 1;
		transform.m_subrect.right = ((uint)m_card.m_value) * 111 + ((uint)m_card.m_value - 1) * 1;
		transform.m_subrect.top = ((uint)m_card.m_suit - 1) * 155 + ((uint)m_card.m_suit - 1) * 1;
		transform.m_subrect.bottom = ((uint)m_card.m_suit) * 155 + ((uint)m_card.m_suit - 1) * 1;
		transform.m_delay = 0;
		transform.m_duration = 1;
		transform.m_startPosition = m_cardDeckPosition;
		transform.m_endPosition = m_targetPosition;
		transform.m_startRotation = 0;
		transform.m_endRotation = 0;
		transform.m_startScale = 1;
		transform.m_endScale = 1;
		transform.m_startAlpha = 1;
		transform.m_endAlpha = 1;
		transform.m_startZDepth = 0;
		transform.m_startZDepth = 1 - 0.05f * m_cardNum;

		dynamicImgDef.m_transforms.push_back( transform );

		// Now create the visualization definition
		Visualization::VisualizationDef visDef;
		visDef.m_dynamicImgDefs.push_back( dynamicImgDef );

		m_pVisualization = new Visualization( visDef );

		// Add to list of active visualizations
		GameVisuals()->m_activeVisualizations.push_back( m_pVisualization );
	}

	/***********/
	/* Methods */
	/***********/
	
	////////////////////
	// ChangePosition //
	////////////////////
	void    
	CardVisual::ChangePosition( GameUtilities::Point2D newPosition )
	{
		m_cardNum = 1;

		// Delete the old visualization
		delete m_pVisualization;

		/* Create the card being split visualization */

		// First create the dynamic image definition
		DynamicImage::DynamicImageDef dynamicImgDef;
		Transform transform;
		transform.m_imagePath = "Data\\CardSheet.png";
		transform.m_subrect.left = ((uint)m_card.m_value - 1) * 111 + ((uint)m_card.m_value - 1) * 1;
		transform.m_subrect.right = ((uint)m_card.m_value) * 111 + ((uint)m_card.m_value - 1) * 1;
		transform.m_subrect.top = ((uint)m_card.m_suit - 1) * 155 + ((uint)m_card.m_suit - 1) * 1;
		transform.m_subrect.bottom = ((uint)m_card.m_suit) * 155 + ((uint)m_card.m_suit - 1) * 1;
		transform.m_delay = 0;
		transform.m_duration = 1;
		transform.m_startPosition = m_targetPosition;
		transform.m_endPosition = newPosition;
		transform.m_startRotation = 0;
		transform.m_endRotation = 0;
		transform.m_startScale = 1;
		transform.m_endScale = 1;
		transform.m_startAlpha = 1;
		transform.m_endAlpha = 1;
		transform.m_startZDepth = 0;
		transform.m_startZDepth = 1 - 0.01f * m_cardNum;

		dynamicImgDef.m_transforms.push_back( transform );

		// Now create the visualization definition
		Visualization::VisualizationDef visDef;
		visDef.m_dynamicImgDefs.push_back( dynamicImgDef );

		m_pVisualization = new Visualization( visDef );

		// Add to list of active visualizations
		GameVisuals()->m_activeVisualizations.push_back( m_pVisualization );
	}

	////////////
	// Update //
	////////////
	void    
	CardVisual::Update()
	{
		m_pVisualization->Update();
	}

	//////////
	// Draw //
	//////////
	void    
	CardVisual::Draw()
	{
		m_pVisualization->Draw();
	}

	////////////////
	// Destructor //
	////////////////
	CardVisual::~CardVisual()
	{
		delete m_pVisualization;
	}

}