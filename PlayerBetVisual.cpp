#include "stdafx.h"

#include "PlayerBetVisual.h"
#include "ServiceProvider.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	PlayerBetVisual::PlayerBetVisual( GameUtilities::Point2D position, uint amt )
	{
		m_betVisualID = ServProvider()->GetGraphicsProvider()->CreateSpriteCollection();

		// Create betting chips sprite
		GameUtilities::IGraphicsProvider::SpriteInfo betInfo;
		betInfo.imageFile = "Data\\PokerChipStack.png";
		betInfo.subrect.left = 0;
		betInfo.subrect.top = 0;
		betInfo.subrect.right = 150;
		betInfo.subrect.bottom = 170;
		betInfo.center = GameUtilities::Point2D( 
			( betInfo.subrect.right - betInfo.subrect.left ) / 2.0f, 
			( betInfo.subrect.bottom - betInfo.subrect.top ) / 2.0f );
		betInfo.position = position;
		betInfo.zDepth = 0.0f;

		ServProvider()->GetGraphicsProvider()->AddSprite( m_betVisualID, "bet", betInfo ); 

		m_betTextID = ServProvider()->GetGraphicsProvider()->CreateTextCollection();

		// Create betting chips text
		GameUtilities::IGraphicsProvider::TextInfo betTextInfo;
		betTextInfo.contents = "$" + NumToStr( amt );
		betTextInfo.fontSize = 1.0f;
		betTextInfo.justification = GameUtilities::IGraphicsProvider::TextInfo::Center;
		betTextInfo.position = position;
		betTextInfo.argb[1] = 255;
		betTextInfo.argb[2] = 0;
		betTextInfo.argb[3] = 0;
			
		ServProvider()->GetGraphicsProvider()->AddText( m_betTextID, "bet_amt", betTextInfo );
	}

	/***********/
	/* Methods */
	/***********/
	
	/////////////////
	// SetPosition //
	/////////////////
	void PlayerBetVisual::SetPosition( GameUtilities::Point2D position )
	{
		// Update bet sprite
		GameUtilities::IGraphicsProvider::SpriteInfo betInfo = ServProvider()->GetGraphicsProvider()->GetSprite( m_betVisualID, "bet" );
		betInfo.position = position;
		ServProvider()->GetGraphicsProvider()->SetSprite( m_betVisualID, "bet", betInfo );

		// Update bet text
		GameUtilities::IGraphicsProvider::TextInfo betTextInfo = ServProvider()->GetGraphicsProvider()->GetText( m_betTextID, "bet_amt" );
		betTextInfo.position = position;
		ServProvider()->GetGraphicsProvider()->SetText( m_betTextID, "bet_amt", betTextInfo );
	}

	///////////////
	// SetAmount //
	///////////////
	void PlayerBetVisual::SetAmount( uint amt )
	{
		// Update bet text
		GameUtilities::IGraphicsProvider::TextInfo betTextInfo = ServProvider()->GetGraphicsProvider()->GetText( m_betTextID, "bet_amt" );
		betTextInfo.contents = "$" + NumToStr( amt );
		ServProvider()->GetGraphicsProvider()->SetText( m_betTextID, "bet_amt", betTextInfo );
	}

	//////////
	// Draw //
	//////////
	void PlayerBetVisual::Draw()
	{
		ServProvider()->GetGraphicsProvider()->DrawSpriteCollection( m_betVisualID );
	}

	//////////////
	// DrawText //
	//////////////
	void PlayerBetVisual::DrawText()
	{
		ServProvider()->GetGraphicsProvider()->DrawTextCollection( m_betTextID );
	}

	////////////////
	// Destructor //
	////////////////
	PlayerBetVisual::~PlayerBetVisual()
	{
		// Free graphical resources
		ServProvider()->GetGraphicsProvider()->DestroySpriteCollection( m_betVisualID );
		ServProvider()->GetGraphicsProvider()->DestroyTextCollection( m_betTextID );
	}

};