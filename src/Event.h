#pragma once
#include <any>
#include <iostream>

enum EventId {TEST};

namespace StarBangBang
{
	struct Event
	{
		EventId id;
		std::any context;
	};
}