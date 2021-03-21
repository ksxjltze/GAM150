#pragma once
#include <any>
#include <iostream>

enum class EventId {DETECTED, PLAY_SOUND, PLAY_MUSIC, STOP_SOUND, TEST, PRINT_TEXT};

namespace StarBangBang
{
	struct Event
	{
		EventId id;
		std::any context;
	};
}