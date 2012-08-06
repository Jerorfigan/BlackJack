#pragma once

#include <string>
#include <vector>

#include "Globals.h"
#include "..\GameUtilities\IGraphicsProvider.h"

namespace BlackJack
{

	class PlayerPrompt
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::vector< std::string > SelectionList;
		typedef std::vector< char > HotKeyList;

		/****************/
		/* Constructors */
		/****************/
	public:
		PlayerPrompt();

		/***********/
		/* Methods */
		/***********/
	public:
		void SetPrompt( uint playerNum, std::string prompt, SelectionList selections, HotKeyList hotKeys );
		void DisplayPrompt();
		void HidePrompt();

		void DrawPromptBackground();
		void DrawPromptText();

		~PlayerPrompt();

		/********/
		/* Data */
		/********/
	private:
		GameUtilities::IGraphicsProvider::TextCollectionID      m_promptID;
		GameUtilities::IGraphicsProvider::SpriteCollectionID    m_promptBackgroundID;
		bool    m_show;
	};

}