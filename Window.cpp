#include "stdafx.h"

/*********************/
/* Homebrew includes */
/*********************/
#include "Application.h"
#include "Window.h"

namespace BlackJack
{

	/* Win32 window callback, which wraps the homebrew Window::WndProc method. */
	LRESULT CALLBACK WndProcWrap(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam )
	{
		return GetWnd()->WndProc( hWnd, uMsg, wParam, lParam );
	}

	/****************/
	/* Constructors */
	/****************/
	Window::Window( std::string title, uint width, uint height ) : 
		m_title( title ), 
		m_width( width ), 
		m_height( height ),
		m_hWnd( NULL ),
		m_pThrownError( NULL )
	{
		if( m_pWindow )
		{
			throw GameError( "[Window::Window]: Attempt to create multiple instances of singleton class Window." );
		}

		m_pWindow = this;
	}


	/***********/
	/* Methods */
	/***********/
	bool Window::HasMessages()
	{
		MSG msg;

		if( PeekMessage( &msg, NULL, 0u, 0u, PM_NOREMOVE ) == 0 )
		{
			// There weren't any messages
			return false;
		}

		return true;
	}

	/* Returns false when processing the WM_QUIT message, true otherwise. */
	bool Window::Pump()
	{
		MSG msg;

		PeekMessage( &msg, NULL, 0u, 0u, PM_REMOVE );

		if( msg.message == WM_QUIT )
			return false;

		TranslateMessage( &msg );
		DispatchMessage( &msg );

		// Check to see if an error occured inside the message handler and throw 
		// the saved error.
		if( m_pThrownError )
		{
			GameError error = *m_pThrownError;
			delete m_pThrownError;
			throw error;
		}

		return true;
	}

	/*******************/
	/* Virtual methods */
	/*******************/
	LRESULT Window::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		try
		{
			switch( uMsg )
			{
			case WM_KEYDOWN:
				{
					if( wParam == VK_ESCAPE )
					{
						DestroyWindow( hWnd );
						return 0;
					}
				}
				break;
			case WM_CREATE:
				{
					m_hWnd = hWnd;
					return 0;
				}
				break;
			case WM_DESTROY:
				{
					PostQuitMessage(0);
					return 0;
				}
				break;				
			}
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
		}
		catch( GameError& error )
		{
			m_pThrownError = new GameError( error );
			return 0;
		}
	}

	void Window::RegisterClass()
	{
			WNDCLASSEX wcex;

			ZeroMemory( &wcex, sizeof(WNDCLASSEX) );

			wcex.cbSize		   = sizeof(WNDCLASSEX); 
			wcex.style		   = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc   = WndProcWrap;
			wcex.cbClsExtra	   = 0;
			wcex.cbWndExtra	   = 0;
			wcex.hInstance	   = GetApp()->GetAppInstance();
			wcex.hIcon		   = 0;
			wcex.hCursor	   = LoadCursor( NULL, IDC_ARROW );
			wcex.hbrBackground = (HBRUSH)COLOR_WINDOW; 
			wcex.lpszMenuName  = 0;
			wcex.lpszClassName = m_title.c_str();
			wcex.hIconSm	   = 0;

			if( RegisterClassEx(&wcex) == 0 )
			{
				throw GameError( "[Window::RegisterClass]: Registering window class failed." );
			}
	}

	void Window::InitInstance()
	{
		DWORD windowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = m_width;
		rc.bottom = m_height;
		AdjustWindowRect( &rc, windowStyle, FALSE );

		/**
		* Usually we capture the return value of CreateWindow,
		* as it is the window handle for our window. However,
		* before CreateWindow finishes, WM_CREATE is called
		* on our window, and we just capture the window handle
		* there.
		*/
		CreateWindow( 
			m_title.c_str(), 
			m_title.c_str(), 
			windowStyle,
			0, 
			0, 
			rc.right - rc.left, 
			rc.bottom - rc.top, 
			NULL, 
			NULL, 
			GetApp()->GetAppInstance(), 
			NULL );

		if ( !m_hWnd )
		{
			throw GameError( "[Window::InitInstance]: Creating window failed." );
		}

		ShowWindow( m_hWnd, SW_SHOW );
	    UpdateWindow( m_hWnd );
	}

	/**************/
	/* Destructor */
	/**************/
	Window::~Window()
	{
		DestroyWindow( m_hWnd );
	}

	/******************/
	/* Static methods */
	/******************/
	void Window::Destroy()
	{
		delete m_pWindow;
		m_pWindow = NULL;
	}

	/***************/
	/* Static data */
	/***************/
	Window* Window::m_pWindow = NULL;

}