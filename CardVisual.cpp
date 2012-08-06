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
	CardVisual::CardVisual( Card card, GameUtilities::Point2D position, uint cardNum, bool splitCard ) :
		m_card( card ), m_targetPosition( position ), m_cardNum( cardNum ), m_splitCard( splitCard )
	{
		/* Create the card being dealt to player visualization */

		// First create the dynamic image definition
		DynamicImage::DynamicImageDef dynamicImgDef;
		Transform transform;
		if( m_card.m_orientation == Card::FaceUp || m_card.m_orientation == Card::FaceUpSideways )
		{
			transform.m_imagePath = "Data\\CardSheet.png";
			transform.m_subrect.left = ((uint)m_card.m_value - 1) * 111 + ((uint)m_card.m_value - 1) * 1;
			transform.m_subrect.right = ((uint)m_card.m_value) * 111 + ((uint)m_card.m_value - 1) * 1;
			transform.m_subrect.top = ((uint)m_card.m_suit - 1) * 155 + ((uint)m_card.m_suit - 1) * 1;
			transform.m_subrect.bottom = ((uint)m_card.m_suit) * 155 + ((uint)m_card.m_suit - 1) * 1;
		}
		else
		{
			transform.m_imagePath = "Data\\CardBack.png";
			transform.m_subrect.left = 0;
			transform.m_subrect.right = 111;
			transform.m_subrect.top = 0;
			transform.m_subrect.bottom = 154;
		}
		transform.m_center = GameUtilities::Point2D( 
			( transform.m_subrect.right - transform.m_subrect.left ) / 2.0f,
			( transform.m_subrect.bottom - transform.m_subrect.top ) / 2.0f );
		transform.m_delay = 0;
		transform.m_duration = 1;
		transform.m_startPosition = m_cardDeckPosition;
		transform.m_endPosition = m_targetPosition;
		transform.m_startRotation = 0;
		if( m_card.m_orientation == Card::FaceUpSideways || m_card.m_orientation == Card::FaceDownSideways )
			transform.m_endRotation = 90;
		else
			transform.m_endRotation = 0;
		transform.m_startScaleX = 1;
		transform.m_endScaleX = 1;
		transform.m_startScaleY = 1;
		transform.m_endScaleY = 1;
		if( m_splitCard )
		{
			transform.m_startAlpha = 0.5f;
			transform.m_endAlpha = 0.5f;
		}
		else
		{
			transform.m_startAlpha = 1;
			transform.m_endAlpha = 1;
		}
		transform.m_startZDepth = 0;
		transform.m_endZDepth = 1 - 0.01f * m_cardNum;

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
		transform.m_center = GameUtilities::Point2D( 
				( transform.m_subrect.right - transform.m_subrect.left ) / 2.0f,
				( transform.m_subrect.bottom - transform.m_subrect.top ) / 2.0f );
		transform.m_delay = 0;
		transform.m_duration = 1;
		transform.m_startPosition = m_targetPosition;
		transform.m_endPosition = newPosition;
		transform.m_startRotation = 0;
		transform.m_endRotation = 0;
		transform.m_startScaleX = 1;
		transform.m_endScaleX = 1;
		transform.m_startScaleY = 1;
		transform.m_endScaleY = 1;
		if( m_splitCard )
		{
			transform.m_startAlpha = 0.5f;
			transform.m_endAlpha = 0.5f;
		}
		else
		{
			transform.m_startAlpha = 1;
			transform.m_endAlpha = 1;
		}
		transform.m_startZDepth = 1 - 0.01f * m_cardNum;
		transform.m_endZDepth = 1 - 0.01f * m_cardNum;

		dynamicImgDef.m_transforms.push_back( transform );

		// Now create the visualization definition
		Visualization::VisualizationDef visDef;
		visDef.m_dynamicImgDefs.push_back( dynamicImgDef );

		m_pVisualization = new Visualization( visDef );

		// Add to list of active visualizations
		GameVisuals()->m_activeVisualizations.push_back( m_pVisualization );
	}

	//////////
	// Flip //
	//////////
	void    
	CardVisual::Flip()
	{
		// Delete the old visualization
		delete m_pVisualization;

		/* Create the card being flipped visualization */
		DynamicImage::DynamicImageDef dynamicImgDef;

		Transform transform1, transform2;
		GetFlipTransforms( transform1, transform2 );

		dynamicImgDef.m_transforms.push_back( transform1 );
		dynamicImgDef.m_transforms.push_back( transform2 );

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

	//////////////////////
	// GetFlipTransform //
	//////////////////////
	void CardVisual::GetFlipTransforms( Transform &transform1, Transform &transform2 )
	{
		transform1.m_delay = transform2.m_delay = 0;
		transform1.m_duration = transform2.m_duration = 0.5f;
		transform1.m_startPosition = transform2.m_startPosition = m_targetPosition;
		transform1.m_endPosition = transform2.m_endPosition = m_targetPosition;
		transform1.m_startRotation = transform2.m_startRotation = 0;
		transform1.m_endRotation = transform2.m_endRotation = 0;
		transform1.m_startScaleY = transform2.m_startScaleY = 1;
		transform1.m_endScaleY = transform2.m_endScaleY = 1;
		transform1.m_startAlpha = transform2.m_startAlpha = 1;
		transform1.m_endAlpha = transform2.m_endAlpha = 1;
		transform1.m_startZDepth = transform2.m_startZDepth = 1 - 0.01f * m_cardNum;
		transform1.m_endZDepth = transform2.m_endZDepth = 1 - 0.01f * m_cardNum;

		transform1.m_startScaleX = 1;
		transform1.m_endScaleX = 0;
		transform2.m_startScaleX = 0;
		transform2.m_endScaleX = 1;

		if( m_card.m_orientation == Card::FaceUp || m_card.m_orientation == Card::FaceUpSideways )
		{
			transform1.m_imagePath = "Data\\CardSheet.png";
			transform1.m_subrect.left = ((uint)m_card.m_value - 1) * 111 + ((uint)m_card.m_value - 1) * 1;
			transform1.m_subrect.right = ((uint)m_card.m_value) * 111 + ((uint)m_card.m_value - 1) * 1;
			transform1.m_subrect.top = ((uint)m_card.m_suit - 1) * 155 + ((uint)m_card.m_suit - 1) * 1;
			transform1.m_subrect.bottom = ((uint)m_card.m_suit) * 155 + ((uint)m_card.m_suit - 1) * 1;
			transform1.m_center = Point2D( 
				( transform1.m_subrect.right - transform1.m_subrect.left ) / 2.0f,
				( transform1.m_subrect.bottom - transform1.m_subrect.top ) / 2.0f );

			transform2.m_imagePath = "Data\\CardBack.png";
			transform2.m_subrect.left = 0;
			transform2.m_subrect.right = 111;
			transform2.m_subrect.top = 0;
			transform2.m_subrect.bottom = 154;
			transform2.m_center = Point2D( 
				( transform2.m_subrect.right - transform2.m_subrect.left ) / 2.0f,
				( transform2.m_subrect.bottom - transform2.m_subrect.top ) / 2.0f );
		}
		else
		{
			transform1.m_imagePath = "Data\\CardBack.png";
			transform1.m_subrect.left = 0;
			transform1.m_subrect.right = 111;
			transform1.m_subrect.top = 0;
			transform1.m_subrect.bottom = 154;
			transform1.m_center = Point2D( 
				( transform1.m_subrect.right - transform1.m_subrect.left ) / 2.0f,
				( transform1.m_subrect.bottom - transform1.m_subrect.top ) / 2.0f );

			transform2.m_imagePath = "Data\\CardSheet.png";
			transform2.m_subrect.left = ((uint)m_card.m_value - 1) * 111 + ((uint)m_card.m_value - 1) * 1;
			transform2.m_subrect.right = ((uint)m_card.m_value) * 111 + ((uint)m_card.m_value - 1) * 1;
			transform2.m_subrect.top = ((uint)m_card.m_suit - 1) * 155 + ((uint)m_card.m_suit - 1) * 1;
			transform2.m_subrect.bottom = ((uint)m_card.m_suit) * 155 + ((uint)m_card.m_suit - 1) * 1;
			transform2.m_center = Point2D( 
				( transform2.m_subrect.right - transform2.m_subrect.left ) / 2.0f,
				( transform2.m_subrect.bottom - transform2.m_subrect.top ) / 2.0f );
		}
	}

}