#include "stdafx.h"

#include "GameInput.h"
#include "GameError.h"
#include "GameVisualizer.h"
#include "ServiceProvider.h"
#include "GameVisualizerInputStructs.h"

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

					sShowPlayerXPrompt promptData;
					promptData.playerIndex = playerNum - 1;
					promptData.prompt = data.prompt;
					promptData.selections = data.choices;
					promptData.hotkeys = data.hotKeys;

					GameVisuals()->Visualize( GameVisualizer::ShowPlayerXPrompt, (void*)&promptData );
				}

				uint choiceIndex = 0;
				for( std::vector< char >::iterator hotKeyItr = data.hotKeys.begin();
					 hotKeyItr != data.hotKeys.end(); ++hotKeyItr )
				{
					if( ServProvider()->GetInputProvider()->IsKeyDown( *hotKeyItr ) )
					{
						data.selectedChoice = data.choices[ choiceIndex ];
						m_waiting4Input = false;

						GameVisuals()->Visualize( GameVisualizer::HidePrompt );
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