#pragma once

#include "Player.h"

namespace BlackJack
{

	class UserPlayer : public Player
	{
		/*******************/
		/* Virtual methods */
		/*******************/
	public:
		virtual bool    CreateStartingBet();
		virtual bool    SelectHandStatus( uint handIndex );       
	};

}