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
	public:
		virtual void DoFrame();

	private:
		virtual void InitGraphics();

		/********/
		/* Data */
		/********/
	private:
		GameUtilities::IGraphicsProvider *m_pGraphicsProvider;
	};

}