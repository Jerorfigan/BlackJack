#pragma once

#include <vector>

#include "Globals.h"
#include "Card.h"
#include "Hand.h"

namespace BlackJack
{

	class Player
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum HandStatus { Hit, Double, Split, Stand, Surrender, Busted };

		/****************/
		/* Constructors */
		/****************/
	public:
		Player();

		/***********/
		/* Methods */
		/***********/
	public:
		void		  AddCardToHand( const Card &card, uint handIndex = 0 );
		void		  DoubleBet( uint handIndex );
		void		  SplitHand( uint handIndex );
		void		  AddChips( uint chips );
		void		  SubtractChips( uint chips );
		void		  ClearBet( uint handIndex );

		HandStatus    GetHandStatus( uint handIndex ) const;
		uint		  GetCurrentBet( uint handIndex ) const;
		uint		  GetNumHands() const;
		uint		  GetHandValue( uint handIndex ) const;
		bool		  CanPlay( uint handIndex ) const;
		bool		  HasBlackJack( uint handIndex ) const;

		/*******************/
		/* Virtual Methods */
		/*******************/
	public:
		~Player() {};

		/************************/
		/* Pure Virtual Methods */
		/************************/
	public:
		virtual bool    CreateStartingBet() = 0;
		virtual bool    SelectHandStatus( uint handIndex ) = 0;

		/********/
		/* Data */
		/********/
	protected:
		std::vector< Hand >		     m_hands;
		std::vector< uint >			 m_currentBets;
		uint						 m_chips;
		std::vector< HandStatus >    m_handStatuses;  
	};

	/***********/
	/* Inlines */
	/***********/
	
	///////////////////
	// GetHandStatus //
	///////////////////
	inline Player::HandStatus	    
	Player::GetHandStatus( uint handIndex ) const
	{
		return m_handStatuses[ handIndex ];
	}

	///////////////////
	// GetCurrentBet //
	///////////////////
	inline uint			
	Player::GetCurrentBet( uint handIndex ) const
	{
		return m_currentBets[ handIndex ];
	}

	/////////////////
	// GetNumHands //
	/////////////////
	inline uint			
	Player::GetNumHands() const
	{
		return m_hands.size();
	}

	//////////////////
	// GetHandValue //
	//////////////////
	inline uint			
	Player::GetHandValue( uint handIndex ) const
	{
		return m_hands[ handIndex ].GetValue();
	}

	/////////////
	// CanPlay //
	/////////////
	inline bool			
	Player::CanPlay( uint handIndex ) const
	{
		return ( m_handStatuses[ handIndex ] == Hit || m_handStatuses[ handIndex ] == Split ) &&
			   m_hands[ handIndex ].GetValue() < 21;
	}

	//////////////////
	// HasBlackJack //
	//////////////////
	inline bool			
	Player::HasBlackJack( uint handIndex ) const
	{
		return m_hands[ handIndex ].HasBlackJack();
	}

}