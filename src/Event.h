#pragma once
#include <any>
#include <iostream>

enum class EventId { COMPUTER_CLICK, DETECTED, PLAY_SOUND, PLAY_MUSIC, STOP_SOUND, TEST, PRINT_TEXT, COLLISION};

namespace StarBangBang
{
	struct Event
	{
		EventId id;
		std::any context;
	};
}