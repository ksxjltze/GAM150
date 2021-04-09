/******************************************************************************/
/*!
\title		Captain Stealth
\file		GameObject.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		GameObject class. Smallest element of the game.
			Contains a Transform struct and a list of components.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "Transform.h"
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <string>

namespace StarBangBang
{
	class GameComponent;
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
			GameComponent* result = nullptr;
			for (GameComponent* component : componentList)
			{

				if (typeid(T).name() == typeid(*component).name())
				{
					result = component;
					break;
				}
			}
			return static_cast<T*>(result);

		}

		inline std::vector<GameComponent*> GetComponents() const
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
		inline void AddComponent(GameComponent* component)
		{
			componentList.push_back(component);
		}
		std::vector<GameComponent*> componentList;
	};
}