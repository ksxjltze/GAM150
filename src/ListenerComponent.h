#pragma once
#include "ComponentCRTP.h"
#include "Event.h"
#include "Observer.h"

namespace StarBangBang
{
	class ListenerComponent : public Component<ListenerComponent>
	{
		public:
			ListenerComponent(GameObject* gameObject) : Component(gameObject) {};
			virtual void onNotify(Event e) {};
	};
}