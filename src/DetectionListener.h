#pragma once
#include "ListenerComponent.h"

namespace StarBangBang
{
	class DetectionListener : public ListenerComponent
	{
	public:
		DetectionListener(GameObject* gameObject);
		virtual void onNotify(Event e);
	};
}