#pragma once

#include <cstdlib>
#include <vector>
#include <map>

#include "Globals.h"
#include "Card.h"
#include "Visualizer.h"
#include "..\GameUtilities\HighResolutionTimer.h"

namespace BlackJack
{

	class GameVisualizer
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum VisualizationType { GameBoard, PlayerXHandYMadeBetZ, PlayerXHandYDealtCardZ, PlayerXHandYSplit, PlayerXSurrender, DealerDeltCardX, 
								 DealerRevealHole, PlayerXWonHandYWinningZ, PlayerXPushedHandY, PlayerXLostHandY, PlayerXAdjustChipsToY };

		/************/
		/* Typedefs */
		/************/
	public: 
		typedef std::vector< Visualizer* > VisualizerList;
		typedef std::map< VisualizationType, Visualizer::ID > VisType2Visualizer;

		/********************/
		/* Internal classes */
		/********************/
	public:
		struct VisType
		{
			VisualizationType    m_type;
		};

		union VisualizationData
		{
			// PlayerXHandYMadeBetZ
			struct 
			{
				uint PlayerNum;
				uint HandIndex;
				uint BetAmount;
			};
			// PlayerXHandYDealtCardZ
			struct
			{
				uint PlayerNum;
				uint HandIndex;
				Card PlayerCard;
			};
			// PlayerXHandYSplit
			struct 
			{
				uint PlayerNum;
				uint HandIndex;
			};
			// PlayerXSurrender
			struct
			{
				uint PlayerNum;
			};
			// DealerDeltCardX
			struct
			{
				Card DealerCard;
			};
			// PlayerXWonHandYWinningZ
			struct
			{
				uint PlayerNum;
				uint HandIndex;
				uint Winnings;
			};
			// PlayerXPushedHandY
			struct
			{
				uint PlayerNum;
				uint HandIndex;
			};
			// PlayerXLostHandY
			struct
			{
				uint PlayerNum;
				uint HandIndex;
			};
			// PlayerXAdjustChipsToY
			struct
			{
				uint PlayerNum;
				uint Chips;
			};
		};

		/******************/
		/* Static Methods */
		/******************/
	public:
		static void				  Create();
		static void			      Destroy();
		static GameVisualizer*    GetGameVisualizer();

		/***************/
		/* Static Data */
		/***************/
	private:
		static GameVisualizer*    m_pGameVisualizer;

		/****************/
		/* Constructors */
		/****************/
	public:
		GameVisualizer();

		/***********/
		/* Methods */
		/***********/
	public:
		Visualization::ID    Visualize( VisualizationType visType, const VisualizationData &data );
		bool			     VisualizationComplete( Visualization::ID id );
		void			     Update();

		~GameVisualizer();

		/********/
		/* Data */
		/********/
	private:
		VisualizerList                        m_visualizers;
		GameUtilities::HighResolutionTimer    m_highResTimer;
		VisType2Visualizer                    m_visType2Visualizer;
	};

	/******************/
	/* Static Inlines */
	/******************/

	///////////////////////
	// GetGameVisualizer //
	///////////////////////
	inline GameVisualizer* 
	GameVisualizer::GetGameVisualizer()
	{
		return m_pGameVisualizer;
	}

	/* Global abbreviated wrapper for GameVisualizer::GetGameVisualizer */
	inline GameVisualizer*
	GameVisuals()
	{
		return GameVisualizer::GetGameVisualizer();
	}

}