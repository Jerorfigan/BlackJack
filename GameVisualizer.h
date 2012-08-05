#pragma once

#include <cstdlib>
#include <vector>
#include <map>

#include "Globals.h"
#include "Card.h"
#include "Visualization.h"
#include "PlayerVisual.h"
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
	private: 
		typedef std::vector< Visualization* > VisualizationList;
		typedef std::vector< PlayerVisual* > PlayerVisualList;

		/********************/
		/* Internal classes */
		/********************/
	public:
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
		void				 Visualize( VisualizationType visType, const VisualizationData &data );
		bool			     VisualizationsComplete();
		void			     Update();
		void                 Draw();

	private:
		void                 AddVisualization( Visualization::ID id, Visualization *pVis );

		~GameVisualizer();

		/********/
		/* Data */
		/********/
	private:
		GameUtilities::HighResolutionTimer    m_highResTimer;
		VisualizationList                     m_activeVisualizations;
		PlayerVisualList					  m_playerVisuals;

		/***********************/
		/* Friend Declarations */
		/***********************/
		friend class CardVisual;
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