#pragma once
#include "Transform.h"
#include <vector>

namespace StarBangBang
{
	class Component;
	class GameObject
	{
	public:
		template <class T>
		inline T* GetComponent()
		{
			return static_cast<T*>(componentList[0]);
		}
		inline void AddComponent(Component* component)
		{
			componentList.push_back(component);
		}

		Transform transform;
		float width = 0, height = 0;
		bool active = true;
		GameObject* parent = nullptr;
	private:
		std::vector<Component*> componentList;
	};
}