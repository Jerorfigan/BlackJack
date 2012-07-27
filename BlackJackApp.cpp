#include "stdafx.h"

#include "BlackJackApp.h"
#include "..\GameUtilities\D3DGraphicsProvider.h"
#include "Window.h"

namespace BlackJack
{

	/* Creates the BlackJack application object. */
	Application* CreateApplication()
	{
		return new BlackJackApp();
	}

	/****************/
	/* Constructors */
	/****************/
	BlackJackApp::BlackJackApp() : Application( "Black Jack", 1280, 800 )
	{

	}

	/*******************/
	/* Virtual methods */
	/*******************/
	void BlackJackApp::DoFrame()
	{
		static bool first = true;
		static GameUtilities::IGraphicsProvider::SpriteCollectionID spriteCollectionID;

		m_pGraphicsProvider->ClearBackbuffer();

		if( first )
		{
			first = false;
			GameUtilities::IGraphicsProvider::SpriteInfo spriteInfo;
			spriteInfo.imageFile = "MyBMP.bmp";
			spriteInfo.alpha = 1;
			spriteInfo.rotation = 0;
			spriteInfo.scale = 1;
			spriteInfo.subrect.bottom = 0;
			spriteInfo.subrect.left = 0;
			spriteInfo.subrect.right = 0;
			spriteInfo.subrect.top = 0;

			spriteCollectionID = m_pGraphicsProvider->CreateSpriteCollection();

			m_pGraphicsProvider->AddSprite( spriteCollectionID, "test", spriteInfo );
		}
		m_pGraphicsProvider->BeginScene();
		m_pGraphicsProvider->StartSpriteBatch();

		m_pGraphicsProvider->DrawSpriteCollection( spriteCollectionID );

		m_pGraphicsProvider->EndSpriteBatch();
		m_pGraphicsProvider->EndScene();

		m_pGraphicsProvider->Flip();
	}

	void BlackJackApp::InitGraphics()
	{
		m_pGraphicsProvider = new GameUtilities::D3DGraphicsProvider( GetWnd()->GetHandle(), 1280, 900 );
	}

}