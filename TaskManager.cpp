#include "stdafx.h"

#include "TaskManager.h"
#include "GameManager.h"
#include "Card.h"
#include "GameVisualizer.h"

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

				m_taskState.StepNumber = 3;
			}
			// TELL PLAYER TO CREATE STARTING BET
		case 3:
			{
				if( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->CreateStartingBet() )
				{
					m_taskState.StepNumber = 4;
				}
			}
			break;
			// VISUALIZE BET
		case 4:
			{
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = pTaskData->HandIndex;
				visData.BetAmount = GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetCurrentBet( pTaskData->HandIndex );

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYMadeBetZ, visData );

				m_taskState.StepNumber = 5;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 5:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.StepNumber = 6;
				}
			}
			break;
			// INCREMENT PLAYER NUMBER
		case 6:
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
				card.m_orientation = Card::FaceUp;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->AddCardToHand( card );

				// Visualize card deal
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = 0;
				visData.PlayerCard = card;

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYDealtCardZ, visData );

				m_taskState.StepNumber = 4;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 4:
			{
				if( GameVisuals()->VisualizationsComplete() )
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
					card.m_orientation = Card::FaceUp;
				}
				else 
				{
					card.m_orientation = Card::FaceDown;
				}
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetDealerAI().AddCardToHand( card );

				// Visualize card deal
				GameVisualizer::VisualizationData visData;
				visData.DealerCard = card;

				GameVisuals()->Visualize( GameVisualizer::DealerDeltCardX, visData );

				m_taskState.StepNumber = 7;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 7:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.StepNumber = 8;
				}
			}
			break;
			// CHECK FOR DEALER BLACK JACK & VISUALIZE
		case 8:
			{
				if( GameMgr()->GetDealerAI().HasBlackJack() )
				{
					GameMgr()->GetDealerAI().RevealHoleCard();

					GameVisualizer::VisualizationData visData;

					GameVisuals()->Visualize( GameVisualizer::DealerRevealHole, visData );

					m_taskState.StepNumber = 9;
				}
				else
				{
					// Task complete
					return true;
				}
			}
			// WAIT FOR DEALER BLACKJACK VISUALIZATION COMPLETION
		case 9:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					// Task complete
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
					// Check to see if any players can still play, otherwise task is complete.
					bool taskComplete = true;

					for( GameManager::PlayerList::iterator playerItr = GameMgr()->GetPlayerList().begin();
						 playerItr != GameMgr()->GetPlayerList().end(); ++playerItr )
					{
						if( (*playerItr)->CanPlay( pTaskData->HandIndex ) )
						{
							taskComplete = false;
							pTaskData->PlayerNumber = 1;
							m_taskState.StepNumber = 3;
							break;
						}
					}

					// Task complete
					return taskComplete;
				}
			}
			// CHECK IF PLAYER CAN PLAY
		case 3:
			{
				if( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->CanPlay( pTaskData->HandIndex ) )
				{
					m_taskState.StepNumber = 4;
				}
				else
				{
					// Skip player's turn.
					m_taskState.StepNumber = 17;
				}
			}
			break;
			// TELL PLAYER TO SELECT PLAY DECISION
		case 4:
			{
				if( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->SelectHandStatus( pTaskData->HandIndex ) )
				{
					m_taskState.StepNumber = 5;
				}
			}
			break;
			// CHECK PLAYER STATUS
		case 5:
			{
				switch( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1]->GetHandStatus( pTaskData->HandIndex ) )
				{
				case Player::Hit:
					{
						m_taskState.StepNumber = 6;
					}
					break;
				case Player::Double:
					{
						m_taskState.StepNumber = 8;
					}
					break;
				case Player::Split:
					{
						m_taskState.StepNumber = 12;
					}
					break;
				case Player::Stand:
					{
						m_taskState.StepNumber = 14;
					}
					break;
				case Player::Surrender:
					{
						m_taskState.StepNumber = 15;
					}
					break;
				}
			}
			break;
			// HIT PLAYER & VISUALIZE
		case 6:
			{
				Card card;
				card.m_orientation = Card::FaceUp;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->AddCardToHand( card, pTaskData->HandIndex );

				// Visualize card deal
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = pTaskData->HandIndex;
				visData.PlayerCard = card;

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYDealtCardZ, visData );

				m_taskState.StepNumber = 7;
			}
			// WAIT FOR HIT PLAYER VISUALIZATION COMPLETION
		case 7:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.StepNumber = 17;
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

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYMadeBetZ, visData );

				m_taskState.StepNumber = 9;
			}
			// WAIT FOR DOUBLE PLAYER BET VISUALIZATION COMPLETION
		case 9:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.StepNumber = 10;
				}
			}
			break;
			// HIT PLAYER WITH DOUBLE CARD & VISUALIZE
		case 10:
			{
				Card card;
				card.m_orientation = Card::FaceUpSideways;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->AddCardToHand( card, pTaskData->HandIndex );

				// Visualize double card
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = pTaskData->HandIndex;
				visData.PlayerCard = card;

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYDealtCardZ, visData );

				m_taskState.StepNumber = 11;
			}
			// WAIT FOR DOUBLE PLAYER CARD VISUALIZATION COMPLETION
		case 11:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.StepNumber = 17;
				}
			}
			break;
			// SPLIT PLAYER'S CARDS & VISUALIZE
		case 12:
			{
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->SplitHand( pTaskData->HandIndex );

				Card card;
				card.m_orientation = Card::FaceUp;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->AddCardToHand( card, pTaskData->HandIndex );
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->AddCardToHand( card, 
					GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->GetNumHands() - 1 );

				// Visualize card split
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;
				visData.HandIndex = pTaskData->HandIndex;

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYSplit, visData );

				m_taskState.StepNumber = 13;
			}
			// WAIT FOR CARD SPLIT VISUALIZATION COMPLETION
		case 13:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					// Don't increment player/index, since need to repeat processing on split hand.
					m_taskState.StepNumber = 2;
				}
			}
			break;
			// STAND & VISUALIZE
		case 14:
			{
				// No visualization for this yet. Just skip player's turn.
				m_taskState.StepNumber = 17;
			}
			break;
			// SURRENDER & VISUALIZE
		case 15:
			{
				// Visualize surrender
				GameVisualizer::VisualizationData visData;
				visData.PlayerNum = pTaskData->PlayerNumber;

				GameVisuals()->Visualize( GameVisualizer::PlayerXSurrender, visData );

				m_taskState.StepNumber = 16;
			}
			// WAIT FOR SURRENDER VISUALIZATION COMPLETION
		case 16:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.StepNumber = 17;
				}
			}
			break;
			// INCREMENT PLAYER & HAND INDEX
		case 17:
			{
				if( pTaskData->HandIndex + 1 >= GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->GetNumHands() )
				{
					pTaskData->PlayerNumber += 1;
					pTaskData->HandIndex = 0;
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
		TaskData *pTaskData;
		pTaskData = (TaskData*) m_taskState.TaskData;

		switch( m_taskState.StepNumber )
		{
			// TASK INITIALIZATION
		case 1:
			{

			}
			// CHECK IF DEALER CAN HIT
		case 2:
			{
				if( GameMgr()->GetDealerAI().CanHit() )
				{
					m_taskState.StepNumber = 3;
				}
				else
				{
					m_taskState.StepNumber = 5;
				}
			}
			break;
			// DRAW DEALER CARD & VISUALIZE
		case 3:
			{
				Card card;
				card.m_orientation = Card::FaceUp;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetDealerAI().AddCardToHand( card );

				// Visualize card deal
				GameVisualizer::VisualizationData visData;
				visData.DealerCard = card;

				GameVisuals()->Visualize( GameVisualizer::DealerDeltCardX, visData );

				m_taskState.StepNumber = 4;
			}
			// WAIT FOR DEALER CARD VISUALIZATION TO COMPLETE
		case 4:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.StepNumber = 2;
				}
			}
			break;
			// REVEAL DEALER HOLE CARD & VISUALIZE
		case 5:
			{
				GameMgr()->GetDealerAI().RevealHoleCard();

				// Visualize hole card reveal
				GameVisualizer::VisualizationData visData;

				GameVisuals()->Visualize( GameVisualizer::DealerRevealHole, visData );
			}
			// WAIT FOR DEALER HOLE REVEAL VISUALIZATION COMPLETION 
		case 6:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					return true;
				}
			}
			break;
		}

		return false;
	}

	/////////////////////
	// ResolveBetsTask //
	/////////////////////
	bool 
	TaskManager::ResolveBetsTask()
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
					// Kill the cards on the table
					GameMgr()->GetDealer().KillCards();

					return true;
				}
			}
			// COMPARE PLAYER'S HAND TO DEALER'S & RESOLVE BET & VISUALIZE
		case 3:
			{
				GameVisualizer::VisualizationData visData;

				if( GameMgr()->GetDealerAI().HasBlackJack() )
				{
					if( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->HasBlackJack( pTaskData->HandIndex ) )
					{
						// Push, recuperate bet
						GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->AddChips( 
							GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetCurrentBet( pTaskData->HandIndex ) );

						GameVisuals()->Visualize( GameVisualizer::PlayerXPushedHandY, visData );
					}
					else
					{
						// Lost hand, don't recuperate bet.
						GameVisuals()->Visualize( GameVisualizer::PlayerXLostHandY, visData );
					}
				}
				else
				{
					visData.PlayerNum = pTaskData->PlayerNumber;
					visData.HandIndex = pTaskData->HandIndex;

					if( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->HasBlackJack( pTaskData->HandIndex ) )
					{
						// Won hand with blackjack, recuperate bet and add winnings paid 3:2
						uint winnings = GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetCurrentBet( pTaskData->HandIndex ) +
							static_cast< uint >( (3.0/2.0) * GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetCurrentBet( pTaskData->HandIndex ) );
						GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->AddChips( winnings );

						visData.Winnings = winnings;

						GameVisuals()->Visualize( GameVisualizer::PlayerXWonHandYWinningZ, visData );
					}
					else if( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetHandValue( pTaskData->HandIndex ) > GameMgr()->GetDealerAI().GetHandValue() )
					{
						// Won hand, recuperate bet and add winnings paid 1:1
						uint winnings = 2 * GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetCurrentBet( pTaskData->HandIndex );
						GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->AddChips( winnings );

						visData.Winnings = winnings;

						GameVisuals()->Visualize( GameVisualizer::PlayerXWonHandYWinningZ, visData );
					}
					else if( GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetHandValue( pTaskData->HandIndex ) == GameMgr()->GetDealerAI().GetHandValue() )
					{
						// Push, recuperate bet
						GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->AddChips( 
							GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->GetCurrentBet( pTaskData->HandIndex ) );

						GameVisuals()->Visualize( GameVisualizer::PlayerXPushedHandY, visData );
					}
					else
					{
						// Lost hand, don't recuperate bet
						GameVisuals()->Visualize( GameVisualizer::PlayerXLostHandY, visData );
					}
				}

				// Now that player chips have been accounted for, clear the bet on this hand.
				GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1 ]->ClearBet( pTaskData->HandIndex );

				m_taskState.StepNumber = 4;
			}
			// WAIT FOR RESULT VISUALIZATION COMPLETION
		case 4:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.StepNumber = 5;
				}
			}
			break;
			// INCREMENT PLAYER NUMBER & HAND INDEX
		case 5:
			{
				if( pTaskData->HandIndex + 1 >= GameMgr()->GetPlayerList()[ pTaskData->PlayerNumber - 1  ]->GetNumHands() )
				{
					pTaskData->PlayerNumber += 1;
					pTaskData->HandIndex = 0;
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