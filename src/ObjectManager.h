/******************************************************************************/
/*!
\title		Captain Stealth
\file		ObjectManager.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Object Manager class.
			Is responsible for the creation of game objects and adding components to them.
			Manages the lifetime of game objects and frees them when the scene is exited.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "CollisionManager.h"
#include "Sprite.h"
#include <vector>
#include <typeinfo>
#include <map>

namespace StarBangBang
{
	class ObjectManager
	{
	public:
		template <class T, class ...Args>
		T& AddComponent(GameObject* gameObject, Args&&... args)
		{
			T* component = new T(gameObject, args...);
			AddComponent(gameObject, component);
			component->objMgr = this;
			return *component;
		}

		template <class T, class U>
		T& AddComponent(GameObject* gameObject)
		{
			T* component = new T<U>(gameObject);
			AddComponent(gameObject, component);
			component->objMgr = this;
			return *component;
		}

		GameObject* Find(const std::string& name);

		BoxCollider& AddCollider(GameObject* gameObject, bool isStatic);

		void AddComponent(GameObject* gameObject, GameComponent* component);
		StarBangBang::ImageComponent* AddImage(GameObject* gameObject, Sprite sprite);
		void AddChildGameObject(GameObject* child, GameObject* parent);

		GameObject* NewGameObject();
		GameObject* NewGameObject(GameObject* parent);

		GameObject* CloneGameObject(GameObject* gameObject);
		void DestroyGameObject(GameObject* gameObject);
		void SaveGameObject(GameObject& gameObject); //Serialize
		GameObject& ReadGameObject(const char* path); //Serialize

		void FreeObjects();
		void FreeComponents();
		void Init();
		void Draw();
		void Update();
		void LateUpdate();
	private:
		friend class Scene;
		std::vector<GameObject*> gameObjectList;
		std::vector<GameComponent*> componentList;

		//For draw order
		std::map<int, std::vector<GameComponent**>> layerMap;
	};
}