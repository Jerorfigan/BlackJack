#include "stdafx.h"

#include "PlayerHUD.h"

namespace BlackJack
{
	/***************/
	/* Static Data */
	/***************/
	const GameUtilities::Point2D    PlayerHUD::m_chipsDispOffset( 0.0f, 150.0f );
	const GameUtilities::Point2D    PlayerHUD::m_nameDispOffset( 0.0f, 200.0f );

	/****************/
	/* Constructors */
	/****************/
	PlayerHUD::PlayerHUD( GameUtilities::Point2D position ) : m_position( position )
	{
		m_playerInfoID = ServProvider()->GetGraphicsProvider()->CreateTextCollection();

		// Create player chips text
		GameUtilities::IGraphicsProvider::TextInfo chipsInfo;
		chipsInfo.contents = "$0";
		chipsInfo.position = m_position + m_chipsDispOffset;
		chipsInfo.justification = GameUtilities::IGraphicsProvider::TextInfo::Center;
		chipsInfo.fontSize = 1;
		chipsInfo.argb[1] = 255;
		chipsInfo.argb[2] = 193;
		chipsInfo.argb[3] = 37;
			
		ServProvider()->GetGraphicsProvider()->AddText( m_playerInfoID, "chips", chipsInfo );

		// Create the player name text
		GameUtilities::IGraphicsProvider::TextInfo nameInfo;
		nameInfo.contents = "";
		nameInfo.position = m_position + m_nameDispOffset;
		nameInfo.justification = GameUtilities::IGraphicsProvider::TextInfo::Center;
		nameInfo.fontSize = 2;
		nameInfo.argb[1] = 0;
		nameInfo.argb[2] = 255;
		nameInfo.argb[3] = 0;

		ServProvider()->GetGraphicsProvider()->AddText( m_playerInfoID, "name", nameInfo );
	}

	/***********/
	/* Methods */
	/***********/
	void PlayerHUD::Draw()
	{
		ServProvider()->GetGraphicsProvider()->DrawTextCollection( m_playerInfoID );
	}

}