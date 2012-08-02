#pragma once

#include <string>
#include <vector>

#include "Globals.h"

namespace BlackJack
{

	class GameInput
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum InputMethod { TextDisplay };

		/********************/
		/* Internal classes */
		/********************/
	public:
		union InputData
		{
			// TextDisplayData
			struct 
			{
				std::string prompt;
				std::vector< std::string > choices;
				std::vector< char > hotKeys;
				std::string selectedChoice;
			};
		};

		/****************/
		/* Constructors */
		/****************/
	public:
		GameInput();

		/***********/
		/* Methods */
		/***********/
	public:
		bool				 GetInput( InputMethod method, InputData &data );

		/******************/
		/* Static Methods */
		/******************/
	public:
		static void			 Create();
		static void			 Destroy();
		static GameInput*    GetGameInput();

		/***************/
		/* Static Data */
		/***************/
	private:
		static GameInput*    m_pGameInput;
	};

	/******************/
	/* Static Inlines */
	/******************/

	//////////////////
	// GetGameInput //
	//////////////////
	inline GameInput*    
	GameInput::GetGameInput()
	{
		return m_pGameInput;
	}

	/* Global wrapper for GameInput::GetGameInput */
	inline GameInput*
	GameInp()
	{
		return GameInput::GetGameInput();
	}
}