#include "stdafx.h"

#include "GameBoardVisual.h"
#include "ServiceProvider.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	GameBoardVisual::GameBoardVisual() : m_visible( false )
	{
		// Create the game board sprite
		m_spriteCollectionID = ServProvider()->GetGraphicsProvider()->CreateSpriteCollection();

		GameUtilities::IGraphicsProvider::SpriteInfo spriteInfo;
		spriteInfo.imageFile = "Data\\GameBoard.jpg";
		spriteInfo.zDepth = 1.0f;

		ServProvider()->GetGraphicsProvider()->AddSprite( m_spriteCollectionID, "game_board", spriteInfo );
	}

	/***********/
	/* Methods */
	/***********/

	///////////////////
	// SetVisibility //
	///////////////////
	void 
	GameBoardVisual::SetVisibility( bool flag )
	{
		m_visible = flag;
	}

	////////////
	// Update //
	////////////
	void 
	GameBoardVisual::Update()
	{

	}

	//////////
	// Draw //
	//////////
	void 
	GameBoardVisual::Draw()
	{
		if( m_visible )
		{
			ServProvider()->GetGraphicsProvider()->DrawSpriteCollection( m_spriteCollectionID );
		}
	}

	////////////////
	// Destructor //
	////////////////
	GameBoardVisual::~GameBoardVisual()
	{
		ServProvider()->GetGraphicsProvider()->DestroySpriteCollection( m_spriteCollectionID );
	}

}