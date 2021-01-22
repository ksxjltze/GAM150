#pragma once
#include "GameObject.h"
#include "Event.h"

namespace StarBangBang
{
	class Observer
	{
	public:
		virtual void onNotify(const GameObject& gameObject, Event event) = 0;
	};
}