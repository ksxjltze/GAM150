#pragma once
#include <any>
#include <iostream>

enum class EventId {DETECTED};

namespace StarBangBang
{
	struct Event
	{
		EventId id;
		std::any context;
	};
}