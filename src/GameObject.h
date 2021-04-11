/******************************************************************************/
/*!
\title		Captain Stealth
\file		GameObject.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
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

		/*!*************************************************************************
		 * \brief 
		 * Default constructor.
		 * Sets the game object to active and default initializes its Transform.
		***************************************************************************/
		GameObject();

		/*!*************************************************************************
		 * \brief
		 * Copy constructor.
		 * Sets the game object to active and copies the transform.
		***************************************************************************/
		GameObject(const GameObject&);

		/*!*************************************************************************
		 * \brief
		 * Finds a component from the game object's component list.
		 * Compares the type of each component in the list and returns the first match.
		 * 
		 * \return Pointer to the first matching component in the list.
		 ***************************************************************************/
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

		/*!*************************************************************************
		 * \brief
		 * Get the list of components for the game object.
		 * 
		 * \return Vector of component pointers.
		 ***************************************************************************/
		inline std::vector<GameComponent*> GetComponents() const
		{
			return componentList;
		}

		/*!*************************************************************************
		 * \brief 
		 * Gets the position of the game object.
		 * \return 
		 * Position Vector of the game object.
		***************************************************************************/
		AEVec2 GetPos();

		/*!*************************************************************************
		 * \brief 
		 * Gets the game object's layer.
		 * \return 
		 * Layer id of the game object.
		***************************************************************************/
		int GetLayer() { return layer; }
		
		/*!*************************************************************************
		 * \brief 
		 * Sets the game object's layer.
		 * \param l
		 * Id of the layer to set.
		***************************************************************************/
		void SetLayer(int l) { layer = l; }

		/*!*************************************************************************
		 * \brief 
		 * Sets the position of the game object.
		 * \param newPos
		 * Position to set.
		***************************************************************************/
		void SetPos(AEVec2 newPos);

		/*!*************************************************************************
		 * \brief 
		 * Sets the game object's active status.
		 * \param status
		 * True if active, false otherwise.
		***************************************************************************/
		void SetActive(bool status);

	private:
		int layer{ 0 };
		friend class ObjectManager;

		/*!*************************************************************************
		 * \brief 
		 * Adds a component to the game object's component list.
		 * \param component
		 * Pointer to the component to add.
		***************************************************************************/
		inline void AddComponent(GameComponent* component)
		{
			componentList.push_back(component);
		}
		std::vector<GameComponent*> componentList;
	};
}