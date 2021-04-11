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
		/*!*************************************************************************
		 * \brief 
		 * Creates and adds a new component to a game object.
		 * \param gameObject
		 * GameObject to attach the component to.
		 * \param ...args
		 * Additional Arguments.
		 * \return 
		 * Reference to the new component.
		***************************************************************************/
		template <class T, class ...Args>
		T& AddComponent(GameObject* gameObject, Args&&... args)
		{
			T* component = new T(gameObject, args...);
			AddComponent(gameObject, component);
			component->objMgr = this;
			return *component;
		}

		/*!*************************************************************************
		 * \brief 
		 * Creates and adds a new component to a game object..
		 * \param gameObject
		 * GameObject to attach the component to.
		 * \return 
		 * Reference to the new component.
		***************************************************************************/
		template <class T, class U>
		T& AddComponent(GameObject* gameObject)
		{
			T* component = new T<U>(gameObject);
			AddComponent(gameObject, component);
			component->objMgr = this;
			return *component;
		}

		/*!*************************************************************************
		 * \brief 
		 * Finds a game object by name.
		 * \param name
		 * Name of the game object to find.
		 * \return 
		 * Pointer to the game object if found.
		 * Returns nullptr if not found.
		***************************************************************************/
		GameObject* Find(const std::string& name);

		/*!*************************************************************************
		 * \brief 
		 * Adds a collider component to the game object.
		 * \param gameObject
		 * GameObject to attach the component to.
		 * \param isStatic
		 * True to set the collider to static, false to set it to dynamic
		 * \return 
		 * Reference to the BoxCollider component that was added.
		***************************************************************************/
		BoxCollider& AddCollider(GameObject* gameObject, bool isStatic);

		/*!*************************************************************************
		 * \brief 
		 * Attaches an existing component to a game object.
		 * \param gameObject
		 * GameObject to attach the component to.
		 * \param component
		 * Component to attach.
		***************************************************************************/
		void AddComponent(GameObject* gameObject, GameComponent* component);

		/*!*************************************************************************
		 * \brief 
		 * Adds an image component to a game object.
		 * \param gameObject
		 * GameObject to attach the component to.
		 * \param sprite
		 * Sprite to be used for drawing the game object.
		 * \return 
		 * Pointer to the Image Component that was added.
		***************************************************************************/
		StarBangBang::ImageComponent* AddImage(GameObject* gameObject, Sprite sprite);

		/*!*************************************************************************
		 * \brief 
		 * Childs a game object to another game object.
		 * \param child
		 * GameObject to child
		 * \param parent
		 * GameObject to set as parent
		***************************************************************************/
		void AddChildGameObject(GameObject* child, GameObject* parent);

		/*!*************************************************************************
		 * \brief 
		 * Creates a new game Object.
		 * \return 
		 * Pointer to the new game object.
		***************************************************************************/
		GameObject* NewGameObject();

		/*!*************************************************************************
		 * \brief 
		 * Creates a new game object and attaches it to a parent game object.
		 * \param parent
		 * Parent GameObject.
		 * \return 
		 * Pointer to the new game object.
		***************************************************************************/
		GameObject* NewGameObject(GameObject* parent);

		/*!*************************************************************************
		 * \brief 
		 * Clones a game object. Copies the transform and components of the game object.
		 * \param gameObject
		 * GameObject to clone.
		 * \return 
		 * The newly cloned game Object
		***************************************************************************/
		GameObject* CloneGameObject(GameObject* gameObject);

		/*!*************************************************************************
		 * \brief 
		 * Destroys game object, freeing the allocated memory.
		 * \param gameObject
		 * GameObject to destroy.
		***************************************************************************/
		void DestroyGameObject(GameObject* gameObject);

		/*!*************************************************************************
		 * \brief 
		 * Saves a game object to a file (WIP).
		 * \param gameObject
		 * Reference to the game object to serialize.
		***************************************************************************/
		void SaveGameObject(GameObject& gameObject); //Serialize

		/*!*************************************************************************
		 * \brief 
		 * Reads a game object from a file (WIP).
		 * \param path Path of the file to read from.
		 * \return
		 * Reference to the new game object.
		***************************************************************************/
		GameObject& ReadGameObject(const char* path); //Serialize

		/*!*************************************************************************
		 * \brief 
		 * Frees all game objects.
		***************************************************************************/
		void FreeObjects();
		
		/*!*************************************************************************
		 * \brief 
		 * Frees all components.
		***************************************************************************/
		void FreeComponents();

		/*!*************************************************************************
		 * \brief 
		 * Initializes the sorting layer and invokes Start() on all game objects.
		***************************************************************************/
		void Init();

		/*!*************************************************************************
		 * \brief 
		 * Draw function. Called once per frame, invokes Draw() on all game objects.
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief
		 * Draw function. Called once per frame, invokes Update() on all game objects.
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief
		 * LateUodate function. Called once per frame after Update(),
		 * invokes LateUpdate() on all game objects.
		***************************************************************************/
		void LateUpdate();
	private:
		friend class Scene;
		std::vector<GameObject*> gameObjectList;
		std::vector<GameComponent*> componentList;

		//For draw order
		std::map<int, std::vector<GameComponent**>> layerMap;
	};
}