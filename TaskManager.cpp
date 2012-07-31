#include "stdafx.h"

#include "TaskManager.h"
#include "GameManager.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	TaskManager::TaskManager()
	{
		// Initialize first task.
		m_taskState.CurrentTask = CollectBets;
		m_taskState.StepNumber = 1;
		m_taskState.TaskData = (void*) new TaskData();
	}

	/***********/
	/* Methods */
	/***********/

	/////////////////
	// PerformTask //
	/////////////////
	void 
	TaskManager::PerformTask()
	{
		switch( m_taskState.CurrentTask )
		{
		case CollectBets:
			{
				if( CollectBetsTask() )
				{
					m_taskState.CurrentTask = DealFirstCard;
					m_taskState.StepNumber = 1;
				}
			}
			break;
		case DealFirstCard:
			{
				if( DealFirstCardTask() )
				{
					m_taskState.CurrentTask = DealSecondCard;
					m_taskState.StepNumber = 1;
				}
			}
			break;
		case DealSecondCard: 
			{
				if( DealSecondCardTask() )
				{
					m_taskState.CurrentTask = QueryPlayers;
					m_taskState.StepNumber = 1;
				}
			}
			break;
		case QueryPlayers:
			{
				if( QueryPlayersTask() )
				{
					m_taskState.CurrentTask = ResolveDealerHand;
					m_taskState.StepNumber = 1;
				}
			}
			break;
		case ResolveDealerHand:
			{
				if( ResolveDealerHandTask() )
				{
					m_taskState.CurrentTask = ResolveBets;
					m_taskState.StepNumber = 1;
				}
			}
			break;
		case ResolveBets:
			{
				if( ResolveBetsTask() )
				{
					// Do nothing, all done.
				}
			}
			break;
		}
	}

	///////////
	// Reset //
	///////////
	void    
	TaskManager::Reset()
	{
		m_taskState.CurrentTask = CollectBets;
		m_taskState.StepNumber = 1;
	}

	/////////////////////
	// CollectBetsTask //
	/////////////////////
	bool 
	TaskManager::CollectBetsTask()
	{
		TaskData *pTaskData;
		pTaskData = (TaskData*) m_taskState.TaskData;

		switch( m_taskState.StepNumber )
		{
			// TASK INITIALIZATION
		case 1:
			{
				pTaskData->PlayerNumber = 1;
			} 
			// VERIFY PLAYER
		case 2:
			{
				if( pTaskData->PlayerNumber > GameMgr()->GetGameConfiguration().NumPlayers )
				{
					// Task complete
					return true;
				}
			}
			// QUERY PLAYER
		case 3:
			{
				m_playerQuerier.ExecuteQuery( PlayerQuerier::CollectBet, pTaskData->PlayerNumber );

				m_taskState.StepNumber = 4;
			}
			// WAIT FOR QUERY COMPLETION
		case 4:
			{
				if( m_playerQuerier.QueryCompleted() )
				{
					m_taskState.StepNumber = 5;
				}
			}
			break;
			// VISUALIZE BET
		case 5:
			{
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;

				pTaskData->VisID = m_gameVisualizer.Visualize( GameVisualizer::PlayerXMadeBet, visData );

				m_taskState.StepNumber = 6;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 6:
			{
				if( m_gameVisualizer.VisualizationComplete( pTaskData->VisID ) )
				{
					m_taskState.StepNumber = 7;
				}
			}
			break;
			// INCREMENT PLAYER NUMBER
		case 7:
			{
				pTaskData->PlayerNumber += 1;

				m_taskState.StepNumber = 2;
			}
			break;
		}

		return false;
	}

	///////////////////////
	// DealFirstCardTask //
	///////////////////////
	bool 
	TaskManager::DealFirstCardTask()
	{
		TaskData *pTaskData;
		pTaskData = (TaskData*) m_taskState.TaskData;

		switch( m_taskState.StepNumber )
		{
			// TASK INITIALIZATION
		case 1:
			{
				pTaskData->PlayerNumber = 1;
			}
		case 2:
			{

			}
		}

		return false;
	}

	////////////////////////
	// DealSecondCardTask //
	////////////////////////
	bool 
	TaskManager::DealSecondCardTask()
	{
		return false;
	}

	//////////////////////
	// QueryPlayersTask //
	//////////////////////
	bool 
	TaskManager::QueryPlayersTask()
	{
		return false;
	}

	///////////////////////////
	// ResolveDealerHandTask //
	///////////////////////////
	bool 
	TaskManager::ResolveDealerHandTask()
	{
		return false;
	}

	/////////////////////
	// ResolveBetsTask //
	/////////////////////
	bool 
	TaskManager::ResolveBetsTask()
	{
		return false;
	}

	/**************/
	/* Destructor */
	/**************/
	TaskManager::~TaskManager()
	{
		// Free task data.
		TaskData *pTaskData = (TaskData*) m_taskState.TaskData;

		delete pTaskData;
	}

}