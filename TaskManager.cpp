#include "stdafx.h"

#include "TaskManager.h"
#include "GameManager.h"
#include "Card.h"
#include "GameVisualizer.h"
#include "GameVisualizerInputStructs.h"

namespace BlackJack
{

	/****************/
	/* Constructors */
	/****************/
	TaskManager::TaskManager()
	{
		// Initialize first task.
		m_taskState.currentTask = CollectBets;
		m_taskState.stepNumber = 1;
		m_taskState.pTaskData = (void*) new TaskData();
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
		switch( m_taskState.currentTask )
		{
		case CollectBets:
			{
				if( CollectBetsTask() )
				{
					m_taskState.currentTask = DealFirstCard;
					m_taskState.stepNumber = 1;
				}
			}
			break;
		case DealFirstCard:
			{
				if( DealFirstCardTask() )
				{
					m_taskState.currentTask = DealSecondCard;
					m_taskState.stepNumber = 1;
				}
			}
			break;
		case DealSecondCard: 
			{
				if( DealSecondCardTask() )
				{
					m_taskState.currentTask = QueryPlayers;
					m_taskState.stepNumber = 1;
				}
			}
			break;
		case QueryPlayers:
			{
				if( QueryPlayersTask() )
				{
					m_taskState.currentTask = ResolveDealerHand;
					m_taskState.stepNumber = 1;
				}
			}
			break;
		case ResolveDealerHand:
			{
				if( ResolveDealerHandTask() )
				{
					m_taskState.currentTask = ResolveBets;
					m_taskState.stepNumber = 1;
				}
			}
			break;
		case ResolveBets:
			{
				if( ResolveBetsTask() )
				{
					m_taskState.currentTask = PromptForNewGame;
					m_taskState.stepNumber = 1;
				}
			}
			break;
		case PromptForNewGame:
			{
				bool newGame = false;

				if( GameMgr()->GetPlayerList()[0]->GetChips() == 0 )
				{
					sShowPlayerXPrompt data;
					data.playerIndex = 0;
					data.prompt = "You lose, you get nothing, good day Sir!";

					GameVisuals()->Visualize( GameVisualizer::ShowPlayerXPrompt, (void*)&data );

					m_taskState.currentTask = DoNothing;
					break;
				}
				
				if( GameMgr()->GetPlayerList()[1]->GetChips() == 0 &&
				    GameMgr()->GetPlayerList()[2]->GetChips() == 0 &&
					GameMgr()->GetPlayerList()[3]->GetChips() )
				{
					sShowPlayerXPrompt data;
					data.playerIndex = 0;
					data.prompt = "You're the last man on the table, good job!";

					GameVisuals()->Visualize( GameVisualizer::ShowPlayerXPrompt, (void*)&data );
				}
				
				if( PromptForNewGameTask( newGame) )
				{
					if( newGame )
					{
						// Start game over.
						GameVisuals()->Reset();
						for( GameManager::PlayerList::iterator playerItr = GameMgr()->GetPlayerList().begin();
							 playerItr != GameMgr()->GetPlayerList().end(); ++playerItr )
						{
							(*playerItr)->Reset();
						}
						GameMgr()->GetDealerAI().Reset();

						m_taskState.currentTask = CollectBets;
						m_taskState.stepNumber = 1;
					}
					else
					{
						m_taskState.currentTask = DoNothing;
					}
				}
			}
			break;
		case DoNothing:
			{

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
		m_taskState.currentTask = CollectBets;
		m_taskState.stepNumber = 1;
	}

	/////////////////////
	// CollectBetsTask //
	/////////////////////
	bool 
	TaskManager::CollectBetsTask()
	{
		TaskData *pTaskData;
		pTaskData = (TaskData*) m_taskState.pTaskData;

		switch( m_taskState.stepNumber )
		{
			// TASK INITIALIZATION
		case 1:
			{
				pTaskData->playerIndex = 0;
				pTaskData->handIndex = 0;
			} 
			// VERIFY PLAYER
		case 2:
			{
				if( pTaskData->playerIndex == GameMgr()->GetGameConfiguration().NumPlayers )
				{
					// Task complete
					return true;
				}

				m_taskState.stepNumber = 3;
			}
			// TELL PLAYER TO CREATE STARTING BET
		case 3:
			{
				if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->CreateStartingBet() )
				{
					m_taskState.stepNumber = 4;
				}
			}
			break;
			// VISUALIZE BET
		case 4:
			{
				sPlayerXHandYMadeBetZ data;
				data.playerIndex = pTaskData->playerIndex;
				data.handIndex = pTaskData->handIndex;
				data.betAmount = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex );

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYMadeBetZ, (void*)&data );

				// Visualize decrease in player's chips
				sPlayerXSetChipsToY chipsData;
				chipsData.playerIndex = pTaskData->playerIndex;
				chipsData.chips = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetChips();

				GameVisuals()->Visualize( GameVisualizer::PlayerXSetChipsToY, (void*)&chipsData );

				m_taskState.stepNumber = 5;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 5:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 6;
				}
			}
			break;
			// INCREMENT PLAYER NUMBER
		case 6:
			{
				pTaskData->playerIndex += 1;

				m_taskState.stepNumber = 2;
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
		pTaskData = (TaskData*) m_taskState.pTaskData;

		switch( m_taskState.stepNumber )
		{
			// TASK INITIALIZATION
		case 1:
			{
				pTaskData->playerIndex = 0;
				pTaskData->handIndex = 0;
			}
			// VERIFY PLAYER
		case 2:
			{
				if( pTaskData->playerIndex == GameMgr()->GetGameConfiguration().NumPlayers )
				{
					// Now deal 1 for the dealer.
					m_taskState.stepNumber = 6;
					break;
				}
			}
			// DEAL CARD TO PLAYER & VISUALIZE
		case 3:
			{
				Card card;
				card.m_orientation = Card::FaceUp;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddCardToHand( card );

				// Visualize card deal
				sPlayerXHandYDealtCardZ data;
				data.playerIndex = pTaskData->playerIndex;
				data.handIndex = 0;
				data.card = card;

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYDealtCardZ, (void*)&data );

				m_taskState.stepNumber = 4;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 4:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 5;
				}
			}
			break;
			// INCREMENT PLAYER NUMBER
		case 5:
			{
				pTaskData->playerIndex += 1;

				m_taskState.stepNumber = 2;
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
				sDealerDeltCardX data;
				data.card = card;

				GameVisuals()->Visualize( GameVisualizer::DealerDeltCardX, (void*)&data );

				m_taskState.stepNumber = 7;
			}
			// WAIT FOR VISUALIZATION COMPLETION
		case 7:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 8;
				}
			}
			break;
			// CHECK FOR DEALER BLACK JACK & VISUALIZE
		case 8:
			{
				if( GameMgr()->GetDealerAI().HasBlackJack() )
				{
					GameMgr()->GetDealerAI().RevealHoleCard();

					GameVisuals()->Visualize( GameVisualizer::DealerRevealHole );

					m_taskState.stepNumber = 9;
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
		pTaskData = (TaskData*) m_taskState.pTaskData;

		switch( m_taskState.stepNumber )
		{
			// TASK INITIALIZATION
		case 1:
			{
				pTaskData->playerIndex = 0;
			}
			// CHECK IF ALL PLAYERS DONE PLAYING
		case 2:
			{
				if( pTaskData->playerIndex == GameMgr()->GetGameConfiguration().NumPlayers )
				{
					// Check to see if any players can still play, otherwise task is complete.
					bool taskComplete = true;

					for( GameManager::PlayerList::iterator playerItr = GameMgr()->GetPlayerList().begin();
						 playerItr != GameMgr()->GetPlayerList().end(); ++playerItr )
					{
						if( (*playerItr)->CanPlay( pTaskData->handIndex ) )
						{
							taskComplete = false;
							pTaskData->playerIndex = 0;
							m_taskState.stepNumber = 3;
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
				if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->CanPlay( pTaskData->handIndex ) )
				{
					m_taskState.stepNumber = 4;
				}
				else
				{
					// Skip player's turn.
					m_taskState.stepNumber = 17;
				}
			}
			break;
			// TELL PLAYER TO SELECT PLAY DECISION
		case 4:
			{
				if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->SelectHandStatus( pTaskData->handIndex ) )
				{
					m_taskState.stepNumber = 5;
				}
			}
			break;
			// CHECK PLAYER STATUS
		case 5:
			{
				switch( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetHandStatus( pTaskData->handIndex ) )
				{
				case Player::Hit:
					{
						m_taskState.stepNumber = 6;
					}
					break;
				case Player::Double:
					{
						m_taskState.stepNumber = 8;
					}
					break;
				case Player::Split:
					{
						m_taskState.stepNumber = 12;
					}
					break;
				case Player::Stand:
					{
						m_taskState.stepNumber = 14;
					}
					break;
				case Player::Surrender:
					{
						m_taskState.stepNumber = 15;
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
				GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddCardToHand( card, pTaskData->handIndex );

				// Visualize card deal
				sPlayerXHandYDealtCardZ data;
				data.playerIndex = pTaskData->playerIndex;
				data.handIndex = pTaskData->handIndex;
				data.card = card;

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYDealtCardZ, (void*)&data );

				m_taskState.stepNumber = 7;
			}
			// WAIT FOR HIT PLAYER VISUALIZATION COMPLETION
		case 7:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 17;
				}
			}
			break;
			// DOUBLE PLAYER BET & VISUALIZE
		case 8:
			{
				GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->DoubleBet( pTaskData->handIndex );

				// Visualize player bet doubling
				sPlayerXHandYMadeBetZ data;
				data.playerIndex = pTaskData->playerIndex;
				data.handIndex = pTaskData->handIndex;
				data.betAmount = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex );

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYMadeBetZ, (void*)&data );

				// Visualize decrease in player's chips
				sPlayerXSetChipsToY chipsData;
				chipsData.playerIndex = pTaskData->playerIndex;
				chipsData.chips = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetChips();

				GameVisuals()->Visualize( GameVisualizer::PlayerXSetChipsToY, (void*)&chipsData );

				m_taskState.stepNumber = 9;
			}
			// WAIT FOR DOUBLE PLAYER BET VISUALIZATION COMPLETION
		case 9:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 10;
				}
			}
			break;
			// HIT PLAYER WITH DOUBLE CARD & VISUALIZE
		case 10:
			{
				Card card;
				card.m_orientation = Card::FaceUpSideways;
				GameMgr()->GetDealer().GetRandomCard( card );
				GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddCardToHand( card, pTaskData->handIndex );

				// Visualize double card
				sPlayerXHandYDealtCardZ data;
				data.playerIndex = pTaskData->playerIndex;
				data.handIndex = pTaskData->handIndex;
				data.card = card;

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYDealtCardZ, (void*)&data );

				m_taskState.stepNumber = 11;
			}
			// WAIT FOR DOUBLE PLAYER CARD VISUALIZATION COMPLETION
		case 11:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 17;
				}
			}
			break;
			// SPLIT PLAYER'S CARDS & VISUALIZE
		case 12:
			{
				GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->SplitHand( pTaskData->handIndex );

				Card card1, card2;
				card1.m_orientation = Card::FaceUp;
				card2.m_orientation = Card::FaceUp;
				GameMgr()->GetDealer().GetRandomCard( card1 );
				GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddCardToHand( card1, pTaskData->handIndex );
				GameMgr()->GetDealer().GetRandomCard( card2 );
				GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddCardToHand( card2, 
					GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetNumHands() - 1 );

				// Visualize card split
				sPlayerXHandYSplit splitData;
				splitData.playerIndex = pTaskData->playerIndex;
				splitData.handIndex = pTaskData->handIndex;
				
				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYSplit, (void*)&splitData );

				// Visualize new cards dealt
				sPlayerXHandYDealtCardZ card1Data;
				card1Data.playerIndex = pTaskData->playerIndex;
				card1Data.handIndex = pTaskData->handIndex;
				card1Data.card = card1;
				
				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYDealtCardZ, (void*)&card1Data );
				
				sPlayerXHandYDealtCardZ card2Data;
				card2Data.playerIndex = pTaskData->playerIndex;
				card2Data.handIndex = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetNumHands() - 1;
				card2Data.card = card2;
				
				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYDealtCardZ, (void*)&card2Data );

				// Visualize new bet
				sPlayerXHandYMadeBetZ betData;
				betData.playerIndex = pTaskData->playerIndex;
				betData.handIndex = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetNumHands() - 1;
				betData.betAmount = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex );

				GameVisuals()->Visualize( GameVisualizer::PlayerXHandYMadeBetZ, (void*)&betData );

				// Visualize decrease in player's chips
				sPlayerXSetChipsToY chipsData;
				chipsData.playerIndex = pTaskData->playerIndex;
				chipsData.chips = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetChips();

				GameVisuals()->Visualize( GameVisualizer::PlayerXSetChipsToY, (void*)&chipsData );

				m_taskState.stepNumber = 13;
			}
			// WAIT FOR CARD SPLIT VISUALIZATION COMPLETION
		case 13:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					// Don't increment player/index, since need to repeat processing on split hand.
					m_taskState.stepNumber = 2;
				}
			}
			break;
			// STAND & VISUALIZE
		case 14:
			{
				// No visualization for this yet. Just skip player's turn.
				m_taskState.stepNumber = 17;
			}
			break;
			// SURRENDER & VISUALIZE
		case 15:
			{
				// Visualize surrender
				sPlayerXSurrender data;
				data.playerIndex = pTaskData->playerIndex;

				GameVisuals()->Visualize( GameVisualizer::PlayerXSurrender, (void*)&data );

				m_taskState.stepNumber = 16;
			}
			// WAIT FOR SURRENDER VISUALIZATION COMPLETION
		case 16:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 17;
				}
			}
			break;
			// INCREMENT PLAYER & HAND INDEX
		case 17:
			{
				if( pTaskData->handIndex + 1 == GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetNumHands() )
				{
					pTaskData->playerIndex += 1;
					pTaskData->handIndex = 0;
				}
				else
				{
					pTaskData->handIndex += 1;
				}

				m_taskState.stepNumber = 2;
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
		pTaskData = (TaskData*) m_taskState.pTaskData;

		switch( m_taskState.stepNumber )
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
					m_taskState.stepNumber = 3;
				}
				else
				{
					m_taskState.stepNumber = 5;
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
				sDealerDeltCardX data;
				data.card = card;

				GameVisuals()->Visualize( GameVisualizer::DealerDeltCardX, (void*)&data );

				m_taskState.stepNumber = 4;
			}
			// WAIT FOR DEALER CARD VISUALIZATION TO COMPLETE
		case 4:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 2;
				}
			}
			break;
			// REVEAL DEALER HOLE CARD & VISUALIZE
		case 5:
			{
				GameMgr()->GetDealerAI().RevealHoleCard();

				// Visualize hole card reveal
				GameVisuals()->Visualize( GameVisualizer::DealerRevealHole );

				m_taskState.stepNumber = 6;
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
		pTaskData = (TaskData*) m_taskState.pTaskData;

		switch( m_taskState.stepNumber )
		{
			// TASK INITIALIZATION
		case 1:
			{
				pTaskData->playerIndex = 0;
			}
			// VERIFY PLAYER
		case 2:
			{
				if( pTaskData->playerIndex == GameMgr()->GetGameConfiguration().NumPlayers )
				{
					// Kill the cards on the table
					GameMgr()->GetDealer().KillCards();

					return true;
				}
			}
			// COMPARE PLAYER'S HAND TO DEALER'S & RESOLVE BET & VISUALIZE
		case 3:
			{
				// 0 - lost hand, 1 - pushed hand, 2 - won hand
				uint winnings = 0;
				uint handStatus = 0;

				if( GameMgr()->GetDealerAI().HasBlackJack() )
				{
					if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->HasBlackJack( pTaskData->handIndex ) )
					{
						// Push, recuperate bet
						winnings = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex );
						GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddChips( winnings );

						handStatus = 1;
					}
					else
					{
						// Lost hand, don't recuperate bet.
						handStatus = 0;
					}
				}
				else if( GameMgr()->GetDealerAI().GetHandValue() <= 21 )
				{
					if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetHandValue( pTaskData->handIndex ) > 21 )
					{
						// Busted
						handStatus = 0;
					}
					else if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->HasBlackJack( pTaskData->handIndex ) )
					{
						// Won hand with blackjack, recuperate bet and add winnings paid 3:2
						winnings = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex ) +
							static_cast< uint >( (3.0/2.0) * GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex ) );
						GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddChips( winnings );
						
						handStatus = 2;
					}
					else if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetHandValue( pTaskData->handIndex ) > GameMgr()->GetDealerAI().GetHandValue() )
					{
						// Won hand, recuperate bet and add winnings paid 1:1
						winnings = 2 * GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex );
						GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddChips( winnings );
						
						handStatus = 2;
					}
					else if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetHandValue( pTaskData->handIndex ) == GameMgr()->GetDealerAI().GetHandValue() )
					{
						// Push, recuperate bet
						winnings = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex );
						GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddChips( winnings );
						
						handStatus = 1;
					}
					else
					{
						// Lost hand, don't recuperate bet
						handStatus = 0;
					}
				}
				else
				{
					// Dealer busted, win if under or at 21
					if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->HasBlackJack( pTaskData->handIndex ) )
					{
						// Won hand with blackjack, recuperate bet and add winnings paid 3:2
						winnings = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex ) +
							static_cast< uint >( (3.0/2.0) * GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex ) );
						GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddChips( winnings );
						
						handStatus = 2;
					}
					else if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetHandValue( pTaskData->handIndex ) <= 21 )
					{
						winnings = 2 * GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetCurrentBet( pTaskData->handIndex );
						GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->AddChips( winnings );
						handStatus = 2;
					}
					else
					{
						handStatus = 0;
					}
				}

				// Visualize
				switch( handStatus )
				{
					// Lost bet
				case 0:
					{
						sPlayerXLostHandY handData;
						handData.playerIndex = pTaskData->playerIndex;
						handData.handIndex = pTaskData->handIndex;

						GameVisuals()->Visualize( GameVisualizer::PlayerXLostHandY, (void*)&handData );
					}
					break;
					// Pushed hand
				case 1:
					{
						sPlayerXPushedHandY handData;
						handData.playerIndex = pTaskData->playerIndex;
						handData.handIndex = pTaskData->handIndex;

						GameVisuals()->Visualize( GameVisualizer::PlayerXPushedHandY, (void*)&handData );

						sPlayerXSetChipsToY chipsData;
						chipsData.playerIndex = pTaskData->playerIndex;
						chipsData.chips = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetChips();

						GameVisuals()->Visualize( GameVisualizer::PlayerXSetChipsToY, (void*)&chipsData );
					}
					break;
					// Won hand
				case 2:
					{
						sPlayerXWonHandY handData;
						handData.playerIndex = pTaskData->playerIndex;
						handData.handIndex = pTaskData->handIndex;

						GameVisuals()->Visualize( GameVisualizer::PlayerXWonHandY, (void*)&handData );

						sPlayerXSetChipsToY chipsData;
						chipsData.playerIndex = pTaskData->playerIndex;
						chipsData.chips = GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetChips();

						GameVisuals()->Visualize( GameVisualizer::PlayerXSetChipsToY, (void*)&chipsData );
					}
					break;
				}

				m_taskState.stepNumber = 4;
			}
			// WAIT FOR RESULT VISUALIZATION COMPLETION
		case 4:
			{
				if( GameVisuals()->VisualizationsComplete() )
				{
					m_taskState.stepNumber = 5;
				}
			}
			break;
			// INCREMENT PLAYER NUMBER & HAND INDEX
		case 5:
			{
				if( pTaskData->handIndex + 1 == GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetNumHands() )
				{
					pTaskData->playerIndex += 1;
					pTaskData->handIndex = 0;
				}
				else
				{
					pTaskData->handIndex += 1;
				}

				m_taskState.stepNumber = 2;
			}
			break;
		}

		return false;
	}

	//////////////////////
	// PromptForNewGame //
	//////////////////////
	bool    
	TaskManager::PromptForNewGameTask( bool &newGame )
	{
		TaskData *pTaskData;
		pTaskData = (TaskData*) m_taskState.pTaskData;

		switch( m_taskState.stepNumber )
		{
			// TASK INITIALIZATION
		case 1:
			{
				pTaskData->playerIndex = 0;
			}
			// VERIFY PLAYER
		case 2:
			{
				if( pTaskData->playerIndex == GameMgr()->GetGameConfiguration().NumPlayers )
				{
					return true;
				}

				m_taskState.stepNumber = 3;
			}
			// CHECK IF PLAYER HAS ANY CHIPS REMAINING
		case 3:
			{
				// Only ask player for new game if they have more than zero chips
				if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->GetChips() == 0 )
				{
					m_taskState.stepNumber = 5;
				}
				m_taskState.stepNumber = 4;
			}
			// ASK PLAYER IF HE'D LIKE A NEW GAME & WAIT FOR RESPONSE
		case 4:
			{
				if( GameMgr()->GetPlayerList()[ pTaskData->playerIndex ]->PlayAgain( newGame ) )
				{
					m_taskState.stepNumber = 5;
				}
			}
			break;
			// INCREMENT PLAYER
		case 5:
			{
				++pTaskData->playerIndex;
			}
			break;
		}
	}

	/**************/
	/* Destructor */
	/**************/
	TaskManager::~TaskManager()
	{
		// Free task data.
		TaskData *pTaskData = (TaskData*) m_taskState.pTaskData;

		delete pTaskData;
	}

}