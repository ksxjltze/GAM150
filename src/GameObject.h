#pragma once
#include "Transform.h"
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <string>

namespace StarBangBang
{
	class _Component;
	class GameObject
	{
	public:
		Transform transform;
		GameObject* parent = nullptr;
		bool active = true;
		bool visible = true;
		
		std::string name;

		GameObject();
		GameObject(const GameObject& prefab);
		GameObject operator=(const GameObject& prefab) { return GameObject(prefab); };

		template <class T>
		inline T* GetComponent()
		{
			_Component* result = nullptr;
			for (_Component* component : componentList)
			{

				if (typeid(T).name() == typeid(*component).name())
				{
					result = component;
					break;
				}
			}
			return static_cast<T*>(result);

		}

		inline std::vector<_Component*> GetComponents() const
		{
			return componentList;
		}


		AEVec2 GetPos();
		int GetLayer() { return layer; }
		void SetLayer(int l) { layer = l; }
		void SetPos(AEVec2 newPos);
		void SetActive(bool);

	private:
		int layer{ 0 };
		friend class ObjectManager;
		inline void AddComponent(_Component* component)
		{
			componentList.push_back(component);
		}
		std::vector<_Component*> componentList;
	};
}