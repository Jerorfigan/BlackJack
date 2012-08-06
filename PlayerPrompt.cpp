#include "stdafx.h"

#include <sstream>

#include "PlayerPrompt.h"
#include "ServiceProvider.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	PlayerPrompt::PlayerPrompt() : m_show( false )
	{
		// Create prompt background
		m_promptBackgroundID = ServProvider()->GetGraphicsProvider()->CreateSpriteCollection();

		GameUtilities::IGraphicsProvider::SpriteInfo spriteInfo;
		spriteInfo.imageFile = "Data\\PromptBackground.jpg";
		spriteInfo.position.x = 0;
		spriteInfo.position.y = 700;
		spriteInfo.subrect.left = 0;
		spriteInfo.subrect.right = 1280;
		spriteInfo.subrect.top = 0;
		spriteInfo.subrect.bottom = 100;
		spriteInfo.zDepth = 0.0f;

		ServProvider()->GetGraphicsProvider()->AddSprite( m_promptBackgroundID, "prompt_background", spriteInfo );

		// Create prompt text resource
		m_promptID = ServProvider()->GetGraphicsProvider()->CreateTextCollection();

		GameUtilities::IGraphicsProvider::TextInfo textInfo;
		ServProvider()->GetGraphicsProvider()->AddText( m_promptID, "prompt", textInfo );
		ServProvider()->GetGraphicsProvider()->AddText( m_promptID, "selections", textInfo );
	}

	/***********/
	/* Methods */
	/***********/
	
	///////////////
	// SetPrompt //
	///////////////
	void 
	PlayerPrompt::SetPrompt( uint playerNum, std::string prompt, SelectionList selections, HotKeyList hotKeys )
	{
		GameUtilities::IGraphicsProvider::TextInfo textInfo;
		textInfo.contents = "Player " + NumToStr( playerNum ) + ": " + prompt;
		textInfo.fontSize = 1;
		textInfo.position.x = 100;
		textInfo.position.y = 720;
		textInfo.argb[0] = 255;
		textInfo.argb[1] = 155;
		textInfo.argb[2] = 155;
		textInfo.argb[3] = 155;

		ServProvider()->GetGraphicsProvider()->SetText( m_promptID, "prompt", textInfo );

		std::string selectionStr;
		uint hotKeyCounter = 0;
		for( SelectionList::iterator selectionItemItr = selections.begin();
			 selectionItemItr != selections.end(); ++selectionItemItr )
		{
			std::stringstream s;
			s << hotKeys[hotKeyCounter++];
			selectionStr += s.str() + " - " + *selectionItemItr + "   ";
		}

		textInfo.contents = selectionStr;
		textInfo.position.y = 760;
		textInfo.argb[1] = 255;
		textInfo.argb[2] = 255;
		textInfo.argb[3] = 255;
		ServProvider()->GetGraphicsProvider()->SetText( m_promptID, "selections", textInfo );
	}

	///////////////////
	// DisplayPrompt //
	///////////////////
	void 
	PlayerPrompt::DisplayPrompt()
	{
		m_show = true;
	}

	////////////////
	// HidePrompt //
	////////////////
	void 
	PlayerPrompt::HidePrompt()
	{
		m_show = false;
	}

	//////////////////////////
	// DrawPromptBackground //
	//////////////////////////
	void PlayerPrompt::DrawPromptBackground()
	{
		if( m_show )
		{
			ServProvider()->GetGraphicsProvider()->DrawSpriteCollection( m_promptBackgroundID );
		}
	}

	////////////////////
	// DrawPromptText //
	////////////////////
	void PlayerPrompt::DrawPromptText()
	{
		if( m_show )
		{
			ServProvider()->GetGraphicsProvider()->DrawTextCollection( m_promptID );
		}
	}

	////////////////
	// Destructor //
	////////////////
	PlayerPrompt::~PlayerPrompt()
	{
		// Free prompt background sprite resource
		ServProvider()->GetGraphicsProvider()->DestroySpriteCollection( m_promptBackgroundID );

		// Free prompt text resource
		ServProvider()->GetGraphicsProvider()->DestroyTextCollection( m_promptID );
	}
}