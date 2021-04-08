#pragma once
#include "Component.h"

//Change to script
namespace StarBangBang
{
	class DragComponent : public GameComponent
	{
	public:
		DragComponent(GameObject* gameObject);
		GameComponent* Clone(GameObject* gameObject, GameComponent* component);
		void Update();
	private:
		bool enabled;
	};
}