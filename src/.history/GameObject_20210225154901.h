#pragma once
<<<<<<< HEAD
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
			_Component* result = nullptr;
			for (_Component* component : componentList)
			{
				if (typeid(T).name() == typeid(*component).name())
				{
					result = component;
					break;
				}
			}
			assert(result != nullptr);
			return static_cast<T*>(result);

		}

		inline std::vector<_Component*> GetComponents() const
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
=======
#include "Rigidbody.h"
#include <typeinfo>
#include <vector>
namespace StarBangBang
{	

	class GameObject 
	{
		public:
			virtual void Init() {};
			virtual void Update() {};
			virtual void Draw() {};
			virtual void Exit() {};
			Transform transform;
			bool isActive = true;
			float width, height;
			
	
>>>>>>> Yg
	};
}