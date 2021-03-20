#pragma once
#include <any>
#include <iostream>

enum class EventId {DETECTED, SOUND};

namespace StarBangBang
{
	struct Event
	{
		EventId id;
		std::any context;
	};
}