#include "stdafx.h"

#include "GameVisualizer.h"
#include "GameError.h"
#include "ServiceProvider.h"

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
	Visualization::ID 
	GameVisualizer::Visualize( VisualizationType visType, const VisualizationData &data )
	{
		return 0;
	}

	///////////////////////////
	// VisualizationComplete //
	///////////////////////////
	bool 
	GameVisualizer::VisualizationComplete( Visualization::ID id )
	{
		return false;
	}

	////////////
	// Update //
	////////////
	void GameVisualizer::Update()
	{
		/* Iterate through the list of visualizers and call update on each one. 
		   The visualizers will also call into the graphics interface at this time, 
		   so essentially this is our drawing loop as well. */

		ServProvider()->GetGraphicsProvider()->ClearBackbuffer();
		ServProvider()->GetGraphicsProvider()->BeginScene();
		ServProvider()->GetGraphicsProvider()->StartSpriteBatch();

		float elapsedTime = m_highResTimer.GetElapsedTimeMilli();
		m_highResTimer.Reset();

		for( VisualizerList::iterator visualizerItr = m_visualizers.begin(); 
			 visualizerItr != m_visualizers.end(); ++visualizerItr )
		{
			(*visualizerItr)->Update( elapsedTime );
		}

		ServProvider()->GetGraphicsProvider()->EndSpriteBatch();
		ServProvider()->GetGraphicsProvider()->EndScene();
		ServProvider()->GetGraphicsProvider()->Flip();
	}

	////////////////
	// Destructor //
	////////////////
	GameVisualizer::~GameVisualizer()
	{
		// Free memory used for visualizers
		for( VisualizerList::iterator visualizerItr = m_visualizers.begin(); 
			 visualizerItr != m_visualizers.end(); ++visualizerItr )
		{
			delete *visualizerItr;
		}
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
	GameVisualizer*    GameVisualizer::m_pGameVisualizer = NULL;

}