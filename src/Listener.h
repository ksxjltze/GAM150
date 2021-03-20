#pragma once
#include "Event.h"

namespace StarBangBang
{
	class Listener
	{
	public:
		virtual void onNotify(Event e) = 0;
	};
}