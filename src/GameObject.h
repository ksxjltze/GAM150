#pragma once
#include "Transform.h"
#include <vector>
#include <typeinfo>

namespace StarBangBang
{
	class Component;
	class GameObject
	{
	public:
		template <class T>
		inline T* GetComponent()
		{
			for (Component* component : componentList)
			{
				if (component->id == T::id)
				{
					return static_cast<T*>(component);
				}
			}
			return nullptr;

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