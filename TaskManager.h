#pragma once

#include "Globals.h"
#include "PlayerQuerier.h"
#include "GameVisualizer.h"

namespace BlackJack
{

	class TaskManager
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum Task { CollectBets, DealFirstCard, DealSecondCard, QueryPlayers, ResolveDealerHand, ResolveBets };

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
			uint					           PlayerNumber;
			GameVisualizer::VisualizationID    VisID;
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
		PlayerQuerier     m_playerQuerier;
		GameVisualizer    m_gameVisualizer;
	};

}