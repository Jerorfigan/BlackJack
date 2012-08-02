#include "stdafx.h"

#include "GameInput.h"
#include "GameError.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	GameInput::GameInput()
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
	GameInput::GetInput( InputMethod method, InputData &data )
	{
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