#pragma once
#include <any>
#include <iostream>

enum class EventId { COMPUTER_CLICK, DETECTED, PLAY_SOUND, PLAY_MUSIC, STOP_SOUND, TEST, PRINT_TEXT, COLLISION, GAME_OVER};

namespace StarBangBang
{
	struct Event
	{
		EventId id{ -1 };
		std::any context;
	};
}