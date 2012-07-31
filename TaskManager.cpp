#include "stdafx.h"

#include "TaskManager.h"
#include "GameManager.h"
#include "Card.h"

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
				pTaskData->HandIndex = 0;
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
			// QUERY PLAYER FOR BET
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
				visData.HandIndex = pTaskData->HandIndex;
				visData.BetAmount = GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetCurrentBet( pTaskData->HandIndex );

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
			// VERIFY PLAYER
		case 2:
			{
				if( pTaskData->PlayerNumber > GameMgr()->GetGameConfiguration().NumPlayers )
				{
					// Now deal 1 for the dealer.
					m_taskState.StepNumber = 6;
					break;
				}
			}
			// DEAL CARD TO PLAYER & VISUALIZE
		case 3:
			{
				Card card;
				card.Orientation = Card::FaceUp;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->AddCardToHand( card );

				// Visualize card deal
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = 0;
				visData.PlayerCard = card;

				pTaskData->VisID = m_gameVisualizer.Visualize( GameVisualizer::PlayerXDealtCardY, visData );

				m_taskState.StepNumber = 4;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 4:
			{
				if( m_gameVisualizer.VisualizationComplete( pTaskData->VisID ) )
				{
					m_taskState.StepNumber = 5;
				}
			}
			break;
			// INCREMENT PLAYER NUMBER
		case 5:
			{
				pTaskData->PlayerNumber += 1;

				m_taskState.StepNumber = 2;
			}
			break;
			// DEAL CARD TO DEALER & VISUALIZE
		case 6:
			{
				Card card;
				if( GameMgr()->GetDealerAI().GetNumCards() == 0 )
				{
					card.Orientation = Card::FaceUp;
				}
				else 
				{
					card.Orientation = Card::FaceDown;
				}
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetDealerAI().AddCardToHand( card );

				// Visualize card deal
				GameVisualizer::VisualizationData visData;
				visData.DealerCard = card;

				pTaskData->VisID = m_gameVisualizer.Visualize( GameVisualizer::DealerDeltCardX, visData );

				m_taskState.StepNumber = 7;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 7:
			{
				if( m_gameVisualizer.VisualizationComplete( pTaskData->VisID ) )
				{
					// Task done.
					return true;
				}
			}
			break;
		}

		return false;
	}

	////////////////////////
	// DealSecondCardTask //
	////////////////////////
	bool 
	TaskManager::DealSecondCardTask()
	{
		return DealFirstCardTask();
	}

	//////////////////////
	// QueryPlayersTask //
	//////////////////////
	bool 
	TaskManager::QueryPlayersTask()
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
			// QUERY PLAYER FOR PLAY
		case 3:
			{
				m_playerQuerier.ExecuteQuery( PlayerQuerier::DeterminePlay, pTaskData->PlayerNumber );

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
			// CHECK PLAYER STATUS
		case 5:
			{
				switch( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1]->GetStatus( pTaskData->HandIndex ) )
				{
				case Player::Hit:
					{
						m_taskState.StepNumber = 6;
					}
					break;
				case Player::Double:
					{

					}
					break;
				case Player::Split:
					{

					}
					break;
				case Player::Stand:
					{
					}
					break;
				case Player::Surrender:
					{

					}
					break;
				}
			}
			break;
			// HIT PLAYER & VISUALIZE
		case 6:
			{
				Card card;
				card.Orientation = Card::FaceUp;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->AddCardToHand( card, pTaskData->HandIndex );

				// Visualize card deal
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = pTaskData->HandIndex;
				visData.PlayerCard = card;

				pTaskData->VisID = m_gameVisualizer.Visualize( GameVisualizer::PlayerXDealtCardY, visData );
			}
			// WAIT FOR HIT PLAYER VISUALIZATION COMPLETION
		case 7:
			{
				if( m_gameVisualizer.VisualizationComplete( pTaskData->VisID ) )
				{
					m_taskState.StepNumber = 10;
				}
			}
			break;
			// DOUBLE PLAYER BET & VISUALIZE
		case 8:
			{
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->DoubleBet( pTaskData->HandIndex );

				// Visualize player bet doubling
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = pTaskData->HandIndex;
				visData.BetAmount = GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->GetCurrentBet( pTaskData->HandIndex );

				pTaskData->VisID = m_gameVisualizer.Visualize( GameVisualizer::PlayerXMadeBet, visData );

				m_taskState.StepNumber = 9;
			}
			// WAIT FOR DOUBLE PLAYER BET VISUALIZATION COMPLETION
		case 9:
			{
				if( m_gameVisualizer.VisualizationComplete( pTaskData->VisID ) )
				{
					m_taskState.StepNumber = 10;
				}
			}
			break;
			// HIT PLAYER WITH DOUBLE CARD & VISUALIZE
		case 10:
			{
				Card card;
				card.Orientation = Card::FaceUpSideways;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->AddCardToHand( card, pTaskData->HandIndex );

				// Visualize double card
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = pTaskData->HandIndex;
				visData.PlayerCard = card;

				pTaskData->VisID = m_gameVisualizer.Visualize( GameVisualizer::PlayerXDealtCardY, visData );

				m_taskState.StepNumber = 11;
			}
			// WAIT FOR DOUBLE PLAYER CARD VISUALIZATION COMPLETION
		case 11:
			{
				if( m_gameVisualizer.VisualizationComplete( pTaskData->VisID ) )
				{
					m_taskState.StepNumber = 12;
				}
			}
			break;
			// INCREMENT PLAYER & HAND INDEX
		case 12:
			{
				if( pTaskData->HandIndex + 1 > GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->GetNumHands() )
				{
					pTaskData->PlayerNumber += 1;	
				}
				else
				{
					pTaskData->HandIndex += 1;
				}

				m_taskState.StepNumber = 2;
			}
			break;
		}

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