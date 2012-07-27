#pragma once

/************************************************/
/************************************************/
/* Wraps the Win32 window and message handling. */
/************************************************/
/************************************************/

/********************************/
/* Third-party library includes */
/********************************/
#include <Windows.h>

/****************/
/* STL includes */
/****************/
#include <string>

/*********************/
/* Homebrew includes */
/*********************/
#include "GameError.h"
#include "Globals.h"

namespace BlackJack
{

	class Window
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		Window( std::string title, uint width, uint height ); 

		/***********/
		/* Methods */
		/***********/
	public:
		bool HasMessages();
		/* Returns false when processing the WM_QUIT message, true otherwise. */
		bool Pump();
		HWND GetHandle();

		/*******************/
		/* Virtual methods */
		/*******************/
	public:
		virtual LRESULT WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
		virtual void RegisterClass();
		virtual void InitInstance();

		/**************/
		/* Destructor */
		/**************/
	public:
		virtual ~Window();

		/********/
		/* Data */
		/********/
	protected:
		std::string    m_title;
		uint		   m_width;
		uint		   m_height;
		HWND		   m_hWnd;
		/* Used to store off any error that gets thrown during the execution of the window procedure, 
		   as we can't throw it then since execution shifts into windows dlls immediately after. */
		GameError*     m_pThrownError;

		/******************/
		/* Static methods */
		/******************/
	public:
		static Window* GetWindow();

		static void Destroy();

		/***************/
		/* Static data */
		/***************/
	private:
		static Window*    m_pWindow;
	};

	/***********/
	/* Inlines */
	/***********/
	inline HWND Window::GetHandle()
	{
		return m_hWnd;
	}

	inline Window* Window::GetWindow()
	{
		return m_pWindow;
	}

	/* Global abbreviated wrapper for Window::GetWindow */
	inline Window* GetWnd()
	{
		return Window::GetWindow();
	}
}