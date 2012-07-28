#include "stdafx.h"

#include "BlackJackApp.h"
#include "..\GameUtilities\D3DGraphicsProvider.h"
#include "..\GameUtilities\DirectInputInputProvider.h"
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

	///////////////
	// InitInput //
	///////////////
	void 
	BlackJackApp::InitInput()
	{
		ServProvider()->RegisterInputProvider( new GameUtilities::DirectInputInputProvider( GetAppInstance(), GetWnd()->GetHandle(), true ) );
	}

	/////////////
	// DoFrame //
	/////////////
	void 
	BlackJackApp::DoFrame()
	{
		static bool first = true;
		static GameUtilities::IGraphicsProvider::SpriteCollectionID spriteCollectionID;
		static GameUtilities::IGraphicsProvider::SpriteInfo spriteInfo;

		ServProvider()->GetGraphicsProvider()->ClearBackbuffer();

		if( first )
		{
			first = false;

			spriteInfo.imageFile = "MyBMP2.bmp";
			spriteInfo.alpha = 1;
			spriteInfo.rotation = 0;
			spriteInfo.scale = 1;
			spriteInfo.subrect.bottom = 0;
			spriteInfo.subrect.left = 0;
			spriteInfo.subrect.right = 0;
			spriteInfo.subrect.top = 0;
			spriteInfo.center.x = 32;
			spriteInfo.center.y = 32;

			spriteCollectionID = ServProvider()->GetGraphicsProvider()->CreateSpriteCollection();

			ServProvider()->GetGraphicsProvider()->AddSprite( spriteCollectionID, "test", spriteInfo );
		}
		ServProvider()->GetGraphicsProvider()->BeginScene();
		ServProvider()->GetGraphicsProvider()->StartSpriteBatch();

		if( ServProvider()->GetInputProvider()->IsKeyDown( 'A' ) )
			spriteInfo.alpha -= 0.01;
		if( ServProvider()->GetInputProvider()->IsKeyDown( 'O' ) )
			spriteInfo.alpha += 0.01;
		if( ServProvider()->GetInputProvider()->IsKeyDown( 'G' ) )
			spriteInfo.scale += 0.01;
		if( ServProvider()->GetInputProvider()->IsKeyDown( 'S' ) )
			spriteInfo.scale -= 0.01;
		if( ServProvider()->GetInputProvider()->IsKeyDown( 'R' ) )
			spriteInfo.rotation += 3;
		if( ServProvider()->GetInputProvider()->IsKeyDown( (UINT)VK_RIGHT ) )
			spriteInfo.position.x += 3.0f;
		if( ServProvider()->GetInputProvider()->IsKeyDown( (UINT)VK_LEFT ) )
			spriteInfo.position.x -= 3.0f;
		if( ServProvider()->GetInputProvider()->IsKeyDown( (UINT)VK_UP ) )
			spriteInfo.position.y -= 3.0f;
		if( ServProvider()->GetInputProvider()->IsKeyDown( (UINT)VK_DOWN ) )
			spriteInfo.position.y += 3.0f;
		ServProvider()->GetGraphicsProvider()->SetSprite( spriteCollectionID, "test", spriteInfo );

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