#pragma once

#include "Globals.h"
#include "Player.h"

namespace BlackJack
{

	class UserPlayer : public Player
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		UserPlayer( uint playerNum ) : Player( playerNum ) {}

		/*******************/
		/* Virtual methods */
		/*******************/
	public:
		virtual bool    CreateStartingBet();
		virtual bool    SelectHandStatus( uint handIndex );   
		virtual bool    PlayAgain( bool &again );
	};

}