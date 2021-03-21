#pragma once
#include "ComponentCRTP.h"
#include "Event.h"
#include "Listener.h"

namespace StarBangBang
{
	class ListenerComponent : public Component<ListenerComponent>, public Listener
	{
		public:
			ListenerComponent(GameObject* gameObject) : Component(gameObject) {};
			virtual void onNotify(Event e) {};
	};
}