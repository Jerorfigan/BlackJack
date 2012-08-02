#pragma once

namespace BlackJack
{

	struct Card
	{
		/****************/
		/* Enumerations */
		/****************/
		enum Suit { Hearts, Diamons, Spades, Clubs };
		enum Value { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
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