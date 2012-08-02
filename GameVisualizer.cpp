#include "stdafx.h"

#include "GameVisualizer.h"
#include "GameError.h"

namespace BlackJack
{
	/****************/
	/* Constructors */
	/****************/
	GameVisualizer::GameVisualizer()
	{
		if( m_pGameVisualizer )
			throw GameError( "[GameVisualizer::GameVisualizer]: Attempt to instantiate multiple instances of singleton GameVisualizer." );

		m_pGameVisualizer = this;
	}

	/***********/
	/* Methods */
	/***********/

	///////////////
	// Visualize //
	///////////////
	GameVisualizer::VisualizationID 
	GameVisualizer::Visualize( VisualizationType visType, const VisualizationData &data )
	{
		return ++m_visIDSequence;
	}

	///////////////////////////
	// VisualizationComplete //
	///////////////////////////
	bool 
	GameVisualizer::VisualizationComplete( VisualizationID ID )
	{
		return false;
	}

	/*******************/
	/* Virtual Methods */
	/*******************/
	GameVisualizer::~GameVisualizer()
	{
	}

	/******************/
	/* Static Methods */
	/******************/

	////////////
	// Create //
	////////////
	void 
	GameVisualizer::Create()
	{
		new GameVisualizer();
	}

	/////////////
	// Destroy //
	/////////////
	void 
	GameVisualizer::Destroy()
	{
		delete m_pGameVisualizer;
		m_pGameVisualizer = NULL;
	}

	/***************/
	/* Static Data */
	/***************/
	GameVisualizer::VisualizationID    GameVisualizer::m_visIDSequence = 1;
	GameVisualizer*					   GameVisualizer::m_pGameVisualizer = NULL;

}