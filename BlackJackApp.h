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
		virtual void InitAppPreServices();
		virtual void InitGraphics();
		virtual void InitInput();
		virtual void InitAppPostServices();

		virtual void DoFrame();

		/**************/
		/* Destructor */
		/**************/
	public:
		virtual ~BlackJackApp();
	};

}