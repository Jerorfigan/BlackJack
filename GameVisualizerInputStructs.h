#pragma once

/**********************************************************************/
/**********************************************************************/
/* List of input data structures associated with visualization types. */
/**********************************************************************/
/**********************************************************************/

#include <string>
#include <vector>

#include "Card.h"
#include "Globals.h"

namespace BlackJack
{

	struct sPlayerXHandYMadeBetZ
	{
		uint playerIndex;
		uint handIndex;
		uint betAmount;
	};

	struct sPlayerXHandYDealtCardZ
	{
		uint playerIndex;
		uint handIndex;
		Card card;
	};
	
	struct sPlayerXHandYSplit
	{
		uint playerIndex;
		uint handIndex;
	};
	
	struct sPlayerXSurrender
	{
		uint playerIndex;
	};
	
	struct sDealerDeltCardX
	{
		Card card;
	};
 
	struct sPlayerXWonHandY
	{
		uint playerIndex;
		uint handIndex;
	};

	struct sPlayerXPushedHandY
	{
		uint playerIndex;
		uint handIndex;
	};

	struct sPlayerXLostHandY
	{
		uint playerIndex;
		uint handIndex;
	};
	
	struct sPlayerXSetChipsToY
	{
		uint playerIndex;
		uint chips;
	};
	
	struct sShowPlayerXPrompt
	{
		uint playerIndex;
		std::string prompt;
		std::vector< std::string > selections;
		std::vector< char > hotkeys;
	};
	
	struct sPlayerXNameChanged
	{
		uint playerIndex;
		std::string name;
	};

}