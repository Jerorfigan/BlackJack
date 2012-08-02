#pragma once

#include "Globals.h"
#include "Visualization.h"

namespace BlackJack
{

	class Visualizer
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef uint ID;

		/****************/
		/* Constructors */
		/****************/
	public:
		Visualizer( ID id ) : m_id( id ) {}

		/*************************/
		/* Pure Virtual Methods  */
		/*************************/
	public:
		virtual void				 Update( float elapsedTimeMilli ) = 0;
		virtual Visualization::ID    CreateVisualization( void* pType, void* pData ) = 0;
		virtual void				 GetVisualizationInfo( Visualization::ID, void* pInfo ) = 0;

		/********/
		/* Data */
		/********/
	protected:
		ID    m_id;
	};

}