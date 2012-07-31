#pragma once

#include "Globals.h"

namespace BlackJack
{

	class PlayerQuerier
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum QueryType { CollectBet, DeterminePlay };

		/****************/
		/* Constructors */
		/****************/
	public:
		PlayerQuerier();

		/***********/
		/* Methods */
		/***********/
	public:
		void    ExecuteQuery( QueryType type, uint playerNum );
		bool    QueryCompleted();

		/**************/
		/* Destructor */
		/**************/
	public:
		~PlayerQuerier();
	};

}