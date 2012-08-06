#pragma once

#include "Globals.h"

namespace BlackJack
{

	class TaskManager
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum Task { CollectBets, DealFirstCard, DealSecondCard, QueryPlayers, ResolveDealerHand, ResolveBets, PromptForNewGame, DoNothing };

		/********************/
		/* Internal classes */
		/********************/
	private:
		struct TaskState
		{
			Task    CurrentTask;
			uint    StepNumber;
			void    *TaskData;
		};

		struct TaskData
		{
			uint			     PlayerNumber;
			uint                 HandIndex;
		};

		/****************/
		/* Constructors */
		/****************/
	public:
		TaskManager();

		/***********/
		/* Methods */
		/***********/
	public:
		/* Tells the TaskManager to perform its current task.
		   TaskManager will handle switching between tasks. */
		void    PerformTask();
		/* Tells TaskManager to start its task cycle over again. */
		void    Reset();

	private:
		/* Task functions returns true if the task is finished. */
		bool    CollectBetsTask();
		bool    DealFirstCardTask();
		bool    DealSecondCardTask();
		bool    QueryPlayersTask();
		bool    ResolveDealerHandTask();
		bool    ResolveBetsTask();
		bool    PromptForNewGameTask( bool &newGame );

		/**************/
		/* Destructor */
		/**************/
	public:
		~TaskManager();

		/********/
		/* Data */
		/********/
	private:
		/* Stores info about the current task being performed. */
		TaskState         m_taskState;
	};

}