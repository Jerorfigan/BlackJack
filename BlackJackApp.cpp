#include "stdafx.h"

#include "BlackJackApp.h"
#include "..\GameUtilities\D3DGraphicsProvider.h"
#include "Window.h"
#include "ServiceProvider.h"

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
	
	/////////////
	// InitApp //
	/////////////
	void 
	BlackJackApp::InitApp()
	{
		ServiceProvider::Create();
	}

	//////////////////
	// InitGraphics //
	//////////////////
	void 
	BlackJackApp::InitGraphics()
	{
		ServProvider()->RegisterGraphicsProvider( new GameUtilities::D3DGraphicsProvider( GetWnd()->GetHandle(), 1280, 900 ) );
	}

	/////////////
	// DoFrame //
	/////////////
	void 
	BlackJackApp::DoFrame()
	{
		static bool first = true;
		static GameUtilities::IGraphicsProvider::SpriteCollectionID spriteCollectionID;

		ServProvider()->GetGraphicsProvider()->ClearBackbuffer();

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

			spriteCollectionID = ServProvider()->GetGraphicsProvider()->CreateSpriteCollection();

			ServProvider()->GetGraphicsProvider()->AddSprite( spriteCollectionID, "test", spriteInfo );
		}
		ServProvider()->GetGraphicsProvider()->BeginScene();
		ServProvider()->GetGraphicsProvider()->StartSpriteBatch();

		ServProvider()->GetGraphicsProvider()->DrawSpriteCollection( spriteCollectionID );

		ServProvider()->GetGraphicsProvider()->EndSpriteBatch();
		ServProvider()->GetGraphicsProvider()->EndScene();

		ServProvider()->GetGraphicsProvider()->Flip();
	}

	/**************/
	/* Destructor */
	/**************/
	BlackJackApp::~BlackJackApp()
	{
		// Destroy service provider.
		ServiceProvider::Destroy();
	}

}