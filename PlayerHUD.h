#pragma once

#include <string>

#include "Globals.h"
#include "..\GameUtilities\IGraphicsProvider.h"
#include "ServiceProvider.h"

namespace BlackJack
{

	class PlayerHUD
	{
		/***************/
		/* Static Data */
		/***************/
	private:
		static const GameUtilities::Point2D    m_chipsDispOffset;
		static const GameUtilities::Point2D    m_nameDispOffset;

		/****************/
		/* Constructors */
		/****************/
	public:
		PlayerHUD( GameUtilities::Point2D position );

		/***********/
		/* Methods */
		/***********/
	public:
		void SetName( std::string name );
		void SetChips( uint chips );

		void Draw();

		/********/
		/* Data */
		/********/
	private:
		GameUtilities::IGraphicsProvider::TextCollectionID    m_playerInfoID;
		GameUtilities::Point2D    m_position;
	};

	/***********/
	/* Inlines */
	/***********/
	
	/////////////
	// SetName //
	/////////////
	inline void 
	PlayerHUD::SetName( std::string name )
	{
		GameUtilities::IGraphicsProvider::TextInfo textInfo = ServProvider()->GetGraphicsProvider()->GetText( m_playerInfoID, "name" );
		textInfo.contents = name;
		ServProvider()->GetGraphicsProvider()->SetText( m_playerInfoID, "name", textInfo );
	}
	
	//////////////
	// SetChips //
	//////////////
	inline void 
	PlayerHUD::SetChips( uint chips )
	{
		GameUtilities::IGraphicsProvider::TextInfo textInfo = ServProvider()->GetGraphicsProvider()->GetText( m_playerInfoID, "chips" );
		textInfo.contents = std::string("$") + NumToStr( chips );
		ServProvider()->GetGraphicsProvider()->SetText( m_playerInfoID, "chips", textInfo );
	}

}