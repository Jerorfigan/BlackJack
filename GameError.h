#pragma once

/**********************************************/
/**********************************************/
/* Object that holds info about a game error. */
/**********************************************/
/**********************************************/

/****************/
/* STL includes */
/****************/
#include <string>

namespace BlackJack
{

	class GameError
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		GameError( std::string errorDescription ) : 
			m_errorDescription( errorDescription )
		{

		}

		/***********/
		/* Methods */
		/***********/
	public:
		std::string GetDescription();

		/********/
		/* Data */
		/********/
	private:
		std::string    m_errorDescription;
	};

	inline std::string GameError::GetDescription() 
	{
		return m_errorDescription;
	}
}