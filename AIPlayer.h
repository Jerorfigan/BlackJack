#pragma once

#include <vector>

#include "Globals.h"
#include "Player.h"
#include "Hand.h"

namespace BlackJack
{

	class AIPlayer : public Player
	{
		/*******************/
		/* Virtual methods */
		/*******************/
	public:
		virtual bool    CreateStartingBet();
		virtual bool    SelectHandStatus( uint handIndex );          
	};

}