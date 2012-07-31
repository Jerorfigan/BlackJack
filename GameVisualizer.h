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
		enum VisualizationType { GameBoard, PlayerXMadeBet, PlayerXDealtCardY, DealerDeltCardX };

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
			// PlayerXMadeBetData
			struct 
			{
				uint PlayerNum;
				uint HandIndex;
				uint BetAmount;
			};
			// PlayerXDealtCardY
			struct
			{
				uint PlayerNum;
				uint HandIndex;
				Card PlayerCard;
			};
			// DealerDeltCardX
			struct
			{
				Card DealerCard;
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