#pragma once

#include "ListenerComponent.h"

namespace StarBangBang
{
	class CollisionListener : public ListenerComponent
	{
	public:
		CollisionListener(GameObject* obj);
		virtual void onNotify(Event e);
	};
}