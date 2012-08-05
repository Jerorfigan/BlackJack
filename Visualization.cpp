#include "stdafx.h"

#include "Visualization.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	Visualization::Visualization( VisualizationDef visDef )
	{
		// Create the dynamic images specified in the visualization definition
		for( std::vector< DynamicImage::DynamicImageDef >::iterator dynImgDefItr = visDef.m_dynamicImgDefs.begin();
			 dynImgDefItr != visDef.m_dynamicImgDefs.end(); ++dynImgDefItr )
		{
			m_dynamicImages.push_back( new DynamicImage( *dynImgDefItr ) );
		}
	}

	/***********/
	/* Methods */
	/***********/
	
	////////////
	// Update //
	////////////
	void 
	Visualization::Update()
	{
		// Update dynamic images
		for( DynamicImageList::iterator dynamicImgItr = m_dynamicImages.begin();
			 dynamicImgItr != m_dynamicImages.end(); ++dynamicImgItr )
		{
			(*dynamicImgItr)->Update();
		}
	}
	
	//////////
	// Draw //
	//////////
	void 
	Visualization::Draw()
	{
		// Draw dynamic images
		for( DynamicImageList::iterator dynamicImgItr = m_dynamicImages.begin();
			 dynamicImgItr != m_dynamicImages.end(); ++dynamicImgItr )
		{
			(*dynamicImgItr)->Draw();
		}
	}

	//////////////
	// Complete //
	//////////////
	bool 
	Visualization::Complete()
	{
		// Visualization is complete if all dynamic images are done animating
		bool visualizationComplete = true;

		for( DynamicImageList::iterator dynamicImgItr = m_dynamicImages.begin();
			 dynamicImgItr != m_dynamicImages.end(); ++dynamicImgItr )
		{
			if( (*dynamicImgItr)->IsAnimating() )
			{
				visualizationComplete = false;
				break;
			}
		}

		return visualizationComplete;
	}

	////////////////
	// Destructor //
	////////////////
	Visualization::~Visualization()
	{
		// Free dynamic images
		for( DynamicImageList::iterator dynamicImgItr = m_dynamicImages.begin();
			 dynamicImgItr != m_dynamicImages.end(); ++dynamicImgItr )
		{
			delete *dynamicImgItr;
		}
	}

}