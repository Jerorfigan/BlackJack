#pragma once

#include <cstdlib>
#include <vector>
#include <map>

#include "Globals.h"
#include "Card.h"
#include "Visualization.h"
#include "PlayerVisual.h"
#include "GameBoardVisual.h"
#include "DealerVisual.h"
#include "PlayerPrompt.h"

namespace BlackJack
{

	class GameVisualizer
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum VisualizationType { GameBoard, PlayerXHandYMadeBetZ, PlayerXHandYDealtCardZ, PlayerXHandYSplit, PlayerXSurrender, DealerDeltCardX, 
								 DealerRevealHole, PlayerXWonHandYWinningZ, PlayerXPushedHandY, PlayerXLostHandY, PlayerXAdjustChipsToY,
		                         ShowPrompt, HidePrompt };

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
			// ShowPrompt
			struct
			{
				uint PlayerNum;
				const char *Prompt;
				const char **Selections;
				uint NumSelections;
				char *HotKeys;
				uint NumHotKeys;
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
		void    Visualize( VisualizationType visType, const VisualizationData &data );
		bool	VisualizationsComplete();
		void    Update();
		void    Draw();
		void    Reset();

		~GameVisualizer();

		/********/
		/* Data */
		/********/
	private:
		VisualizationList    m_activeVisualizations;
		PlayerVisualList	 m_playerVisuals;
		GameBoardVisual      m_gameBoardVisual;
		DealerVisual		 m_dealerVisual;
		PlayerPrompt         m_playerPrompt;

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