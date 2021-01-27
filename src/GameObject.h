#pragma once
#include "Transform.h"
#include <vector>
#include <typeinfo>
#include <algorithm>

namespace StarBangBang
{
	class _Component;
	class GameObject
	{
	public:
		GameObject();
		GameObject(const GameObject& prefab);
		GameObject operator=(const GameObject& prefab) { return GameObject(prefab); };

		template <class T>
		inline T* GetComponent()
		{
			for (_Component* component : componentList)
			{
				if (typeid(T).name() == typeid(*component).name())
				{
					return static_cast<T*>(component);
				}
			}
			return nullptr;

		}

		inline std::vector<_Component*> GetComponents()
		{
			return componentList;
		}

		Transform transform;
		GameObject* parent = nullptr;

		float width = 0, height = 0;
		bool active = true;

		AEVec2 GetPos();
		void SetPos(AEVec2 newPos);

	private:
		friend class ObjectManager;
		inline void AddComponent(_Component* component)
		{
			componentList.push_back(component);
		}
		std::vector<_Component*> componentList;
	};
}