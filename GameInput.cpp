#include "stdafx.h"

#include "GameInput.h"
#include "GameError.h"
#include "GameVisualizer.h"
#include "ServiceProvider.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	GameInput::GameInput() : m_waiting4Input( false )
	{
		if( m_pGameInput )
			throw GameError( "[GameInput::GameInput]: Attempt to instantiate multiple instances of singleton GameInput." );

		m_pGameInput = this;
	}

	/***********/
	/* Methods */
	/***********/

	//////////////
	// GetInput //
	//////////////
	bool    
	GameInput::GetInput( uint playerNum, InputMethod method, InputData &data )
	{
		switch( method )
		{
		case TextPrompt:
			{
				if( !m_waiting4Input )
				{
					m_waiting4Input = true;

					GameVisualizer::VisualizationData visData;
					visData.PlayerNum = playerNum;
					visData.Prompt = data.prompt.c_str();
					
					// Have to pack selection/hotkey data in char arrays since a union can't hold STL types apparently.
					const char **selections = new const char*[ data.choices.size() ]; 
					uint index = 0;
					for( std::vector< std::string >::iterator choiceItr = data.choices.begin();
						 choiceItr != data.choices.end(); ++choiceItr )
					{
						selections[ index++ ] = choiceItr->c_str();
					}
					visData.Selections = selections;
					visData.NumSelections = data.choices.size();

					char *hotkeys = new char[ data.hotKeys.size() ];
					index = 0;
					for( std::vector< char >::iterator hotKeyItr = data.hotKeys.begin();
						 hotKeyItr != data.hotKeys.end(); ++hotKeyItr )
					{
						hotkeys[ index++ ] = *hotKeyItr;
					}
					visData.HotKeys = hotkeys;
					visData.NumHotKeys = data.hotKeys.size();

					GameVisuals()->Visualize( GameVisualizer::ShowPrompt, visData );
				}

				uint choiceIndex = 0;
				for( std::vector< char >::iterator hotKeyItr = data.hotKeys.begin();
					 hotKeyItr != data.hotKeys.end(); ++hotKeyItr )
				{
					if( ServProvider()->GetInputProvider()->IsKeyDown( *hotKeyItr ) )
					{
						data.selectedChoice = data.choices[ choiceIndex ];
						m_waiting4Input = false;
						GameVisualizer::VisualizationData visData;
						GameVisuals()->Visualize( GameVisualizer::HidePrompt, visData );
						return true;
					}
					++choiceIndex;
				}
			}
			break;
		}

		return false;
	}

	/******************/
	/* Static Methods */
	/******************/

	////////////
	// Create //
	////////////
	void			 
	GameInput::Create()
	{
		new GameInput();
	}

	/////////////
	// Destroy //
	/////////////
	void			 
	GameInput::Destroy()
	{
		delete m_pGameInput;
		m_pGameInput = NULL;
	}

	/***************/
	/* Static Data */
	/***************/
	GameInput*    GameInput::m_pGameInput = NULL;

}