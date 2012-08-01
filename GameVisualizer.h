#pragma once

#include <cstdlib>

#include "Globals.h"
#include "Card.h"

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
		typedef std::size_t VisualizationID;   

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

		/****************/
		/* Constructors */
		/****************/
	public:
		GameVisualizer();

		/***********/
		/* Methods */
		/***********/
	public:
		VisualizationID Visualize( VisualizationType visType, const VisualizationData &data );
		bool VisualizationComplete( VisualizationID ID );

		/***************/
		/* Destructors */
		/***************/
	public:
		~GameVisualizer();

		/***************/
		/* Static data */
		/***************/
	private:
		static VisualizationID    m_visIDSequence;
	};

}