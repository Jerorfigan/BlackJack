#include "stdafx.h"

#include "Application.h"
#include "GameError.h"
#include "Window.h"

/****************************/
/* Application entry point. */
/****************************/
int APIENTRY WinMain( HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR     lpCmdLine,
                      int       nCmdShow )
{
	using namespace BlackJack;

	// Seed random number generator.
	srand( GetTickCount() );

	try
	{
		CreateApplication();

		// Store the app instance handle for later use.
		GetApp()->SetAppInstance( hInstance );

		GetApp()->Init();
		GetApp()->Run();
	}
	catch( GameError& error )
	{
		MessageBox( NULL, error.GetDescription().c_str(), "Game Error!", MB_OK|MB_ICONEXCLAMATION );
	}

	// Cleanup the application.
	Application::Kill();

	return 0;
}

namespace BlackJack
{
		
		/****************/
		/* Constructors */
		/****************/
		Application::Application( std::string title, uint width, uint height ) :
			m_title( title ), 
			m_wndWidth( width ),
			m_wndHeight( height ),
			m_isActive( true )
		{
			if( m_pApplication )
			{
				throw GameError( "[Application::Application]: Attempt to create multiple instances of singleton class Application." );
			}

			m_pApplication = this;
		}

		/***********/
		/* Methods */
		/***********/
		void Application::Init()
		{
			InitPrimaryWindow();
			InitGraphics();
			InitInput();
			InitSound();
			InitExtraSubsystems();
		}

		void Application::Run()
		{
			bool finished = false;

			while( !finished )
			{
				// Check for messages and process if any.
				while( !finished && GetWnd()->HasMessages() )
				{
					if( !GetWnd()->Pump() )
					{
						finished = true;
					}
				}
				
				if( m_isActive )
				{
					DoFrame();
				}
				else
				{
					DoIdleFrame();
				}
			}
		}

		void Application::Pause()
		{
			m_isActive = false;
		}

		void Application::Unpause()
		{
			m_isActive = true;
		}

		void Application::SetAppInstance( HINSTANCE hInstance )
		{
			m_hInstance = hInstance;
		}

		/*******************/
		/* Virtual Methods */
		/*******************/
		void Application::DoFrame()
		{

		}

		void Application::DoIdleFrame()
		{
			// Poll to see if we can get the graphics device back for rendering.
			/*HRESULT hr = Graphics()->GetD3DDevice()->TestCooperativeLevel();

			if( hr == D3D_OK )
			{
				GetApp()->Pause( false );
			}
			else if( hr == D3DERR_DEVICELOST )
			{
				Sleep(500);
			}
			else if( hr == D3DERR_DEVICENOTRESET )
			{
				GetImgMgr()->ReleaseAllImageResources();
				Graphics()->ReleaseBackBuffRef();

				Graphics()->Reset();

				GetApp()->Pause( false );
			}
			else
			{
				throw GameError( "[Application::DoIdleFrame]: Call to IDirect3DDevice9::TestCooperativeLevel returned D3DERR_DRIVERINTERNALERROR." );
			}*/
		}

		void Application::InitPrimaryWindow()
		{
			new Window( m_title, m_wndWidth, m_wndHeight );

			GetWnd()->RegisterClass();
			GetWnd()->InitInstance();
		}

		void Application::InitGraphics()
		{
			
		}

		void Application::InitInput()
		{

		}

		void Application::InitSound()
		{

		}

		void Application::InitExtraSubsystems()
		{

		}

		/**************/
		/* Destructor */
		/**************/
		Application::~Application()
		{
			
		}

		/******************/
		/* Static methods */
		/******************/
		void Application::Kill()
		{
			// Destroy the primary window.
			Window::Destroy();

			// Destroy the application object.
			delete m_pApplication;
			m_pApplication = NULL;
		}

		/***************/
		/* Static data */
		/***************/
		Application* Application::m_pApplication = NULL;

}