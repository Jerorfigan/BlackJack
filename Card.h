#pragma once

namespace BlackJack
{

	struct Card
	{
		/****************/
		/* Enumerations */
		/****************/
		enum Suit { Clubs = 1, Diamonds, Hearts, Spades };
		enum Value { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
		enum Orientation { FaceDown, FaceDownSideways, FaceUp, FaceUpSideways };

		/****************/
		/* Constructors */
		/****************/
		Card() {}
		Card( Suit suit, Value value, Orientation orientation = FaceDown ) : m_suit(suit), m_value( value), m_orientation( orientation ) {}

		Suit m_suit;
		Value m_value;
		Orientation m_orientation;
	};

}