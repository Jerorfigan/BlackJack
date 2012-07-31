#pragma once

#include <vector>

#include "Globals.h"
#include "PlayerConfiguration.h"
#include "DealerConfiguration.h"

namespace BlackJack
{

	struct GameConfiguration
	{
		uint							      NumPlayers;
		std::vector< PlayerConfiguration >    PlayerConfigs;
		DealerConfiguration					  DealerConfig;
		bool								  AllowSplit;
		bool								  AllowSurrender;
	};

}