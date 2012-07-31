#include "stdafx.h"

#include "GameVisualizer.h"

namespace BlackJack
{
	/****************/
	/* Constructors */
	/****************/
	GameVisualizer::GameVisualizer()
	{

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

	/***************/
	/* Destructors */
	/***************/
	GameVisualizer::~GameVisualizer()
	{

	}

	/***************/
	/* Static data */
	/***************/
	GameVisualizer::VisualizationID    GameVisualizer::m_visIDSequence = 1;
}