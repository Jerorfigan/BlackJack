#pragma once

/***************************************************/
/***************************************************/
/* Drives the application initialization and loop. */
/***************************************************/
/***************************************************/

/********************************/
/* Third-party library includes */
/********************************/
#include <Windows.h>

/*********************/
/* Homebrew includes */
/*********************/
#include "GameError.h"
#include "Globals.h"

namespace BlackJack
{
	
	class Application
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		Application( std::string title, uint width, uint height );

		/***********/
		/* Methods */
		/***********/
	public:
		void Init();
		void Run();
		void Pause();
		void Unpause();
		HINSTANCE GetAppInstance();
		void SetAppInstance( HINSTANCE hInstance );

		/*******************/
		/* Virtual Methods */
		/*******************/
	private:
		virtual void InitApp();
		virtual void InitPrimaryWindow();
		virtual void InitGraphics();
		virtual void InitInput();
		virtual void InitSound();
		virtual void InitExtraSubsystems();

		virtual void DoFrame();
		virtual void DoIdleFrame();

		/**************/
		/* Destructor */
		/**************/
	public:
		virtual ~Application();

		/********/
		/* Data */
		/********/
	protected:
		std::string    m_title;
		uint           m_wndWidth;
		uint           m_wndHeight;
		bool           m_isActive;
		HINSTANCE      m_hInstance;

		/******************/
		/* Static methods */
		/******************/
	public:
		static Application* GetApplication();

		static void Kill();

		/***************/
		/* Static data */
		/***************/
	private:
		static Application*    m_pApplication;
	};

	/***********/
	/* Inlines */
	/***********/
	inline HINSTANCE Application::GetAppInstance()
	{
		return m_hInstance;
	}

	inline Application* Application::GetApplication()
	{
		return m_pApplication;
	}

	/* Global abbreviated wrapper for Application::GetApplication */
	inline Application* GetApp()
	{
		return Application::GetApplication();
	}

	/* CreateApplication function which will be implemented by the subclassing application. */
	Application* CreateApplication();

}