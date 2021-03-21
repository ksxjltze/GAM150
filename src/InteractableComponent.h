#pragma once
#include "ComponentCRTP.h"

namespace StarBangBang
{
	class InteractableComponent : public Component<InteractableComponent>
	{
	public:
		InteractableComponent(GameObject* obj);
	};
}