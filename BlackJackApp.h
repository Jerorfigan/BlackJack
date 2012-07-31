#pragma once

/*********************************/
/*********************************/
/* Drives the game of BlackJack. */
/*********************************/
/*********************************/

#include "Application.h"
#include "..\GameUtilities\IGraphicsProvider.h"

namespace BlackJack
{

	class BlackJackApp : public Application
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		BlackJackApp();

		/*******************/
		/* Virtual methods */
		/*******************/
	private:
		virtual void InitApp();
		virtual void InitGraphics();
		virtual void InitInput();

		virtual void DoFrame();

		/**************/
		/* Destructor */
		/**************/
	public:
		virtual ~BlackJackApp();
	};

}