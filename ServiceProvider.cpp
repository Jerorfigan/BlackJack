#include "stdafx.h"

#include "ServiceProvider.h"

namespace BlackJack
{
	/***************/
	/* Constructor */
	/***************/
	ServiceProvider::ServiceProvider() 
	{
		if( m_pServiceProvider )
		{
			throw GameError( "[ServiceProvider::ServiceProvider]: Attempt to instantiate multiple instances of singleton class ServiceProvider." );
		}

		m_pServiceProvider = this;
	}

	/***********/
	/* Methods */
	/***********/

	//////////////////////////////
	// RegisterGraphicsProvider //
	//////////////////////////////
	void								 
	ServiceProvider::RegisterGraphicsProvider( GameUtilities::IGraphicsProvider *pGraphicsProvider )
	{
		m_pGraphicsProvider = pGraphicsProvider;
	}

	/******************/
	/* Static methods */
	/******************/
	
	////////////
	// Create //
	////////////
	void 
	ServiceProvider::Create()
	{
		new ServiceProvider();
	}

	/////////////
	// Destroy //
	/////////////
	void 
	ServiceProvider::Destroy()
	{
		delete m_pServiceProvider;
		m_pServiceProvider = NULL;
	}

	/**************/
	/* Destructor */
	/**************/
	ServiceProvider::~ServiceProvider()
	{
		// Free graphics provider.
		delete m_pGraphicsProvider;
	}

	/***************/
	/* Static data */
	/***************/
	ServiceProvider    *ServiceProvider::m_pServiceProvider;

}