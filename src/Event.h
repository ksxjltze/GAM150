#pragma once
#include <any>
#include <iostream>

enum class EventId {DETECTED, PLAY_SOUND, PLAY_MUSIC, STOP_SOUND};

namespace StarBangBang
{
	struct Event
	{
		EventId id;
		std::any context;
	};
}