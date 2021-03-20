#pragma once
#include <any>
#include <iostream>

enum class EventId {DETECTED, PLAY_SOUND, PLAY_MUSIC};

namespace StarBangBang
{
	struct Event
	{
		EventId id;
		std::any context;
	};
}