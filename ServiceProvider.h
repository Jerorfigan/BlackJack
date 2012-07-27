#pragma once

/**********************************/
/**********************************/
/* Manages all required services. */
/**********************************/
/**********************************/

#include "..\GameUtilities\IGraphicsProvider.h"
#include "GameError.h"

namespace BlackJack
{

	class ServiceProvider
	{
		/***************/
		/* Constructor */
		/***************/
	public:
		ServiceProvider();

		/***********/
		/* Methods */
		/***********/
	public:
		void								 RegisterGraphicsProvider( GameUtilities::IGraphicsProvider *pGraphicsProvider );
		GameUtilities::IGraphicsProvider*    GetGraphicsProvider();

		/**************/
		/* Destructor */
		/**************/
	public:
		~ServiceProvider();

		/********/
		/* Data */
		/********/
	private:
		GameUtilities::IGraphicsProvider    *m_pGraphicsProvider;

		/******************/
		/* Static methods */
		/******************/
	public:
		static void				   Create();
		static void				   Destroy();
		static ServiceProvider*    GetServiceProvider();

		/***************/
		/* Static data */
		/***************/
	private:
		static ServiceProvider    *m_pServiceProvider;
	};

	/***********/
	/* Inlines */
	/***********/
	
	/////////////////////////
	// GetGraphicsProvider //
	/////////////////////////
	inline GameUtilities::IGraphicsProvider*    
	ServiceProvider::GetGraphicsProvider()
	{
		return m_pGraphicsProvider;
	}

	/******************/
	/* Static inlines */
	/******************/

	////////////////////////
	// GetServiceProvider //
	////////////////////////
	inline ServiceProvider* 
	ServiceProvider::GetServiceProvider()
	{
		return m_pServiceProvider;
	}

	/***********************************************************************/
	/* Global abbreviated wrapper for ServiceProvider::GetServiceProvider. */
	/***********************************************************************/
	inline ServiceProvider* 
	ServProvider()
	{
		return ServiceProvider::GetServiceProvider();
	}

}