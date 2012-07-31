#pragma once

namespace BlackJack
{

	struct Card
	{
		enum Suit { Hearts, Diamons, Spades, Clubs };
		enum Value { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
		enum Orientation { FaceDown, FaceDownSideways, FaceUp, FaceUpSideways };

		Suit Suit;
		Value Value;
		Orientation Orientation;
	};

}