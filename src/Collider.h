/******************************************************************************/
/*!
\title		Captain Stealth
\file		Collider.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the declaration for Collider.cpp
			Contains collider class and functions
			for collision

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "GameObject.h"
#include "ComponentCRTP.h"
#include "Physics.h"

namespace StarBangBang
{


	class Collider : public Component<Collider>
	{

	public:
		bool isTrigger = false;
		//collider does not move
		bool isStatic = false;
		AEVec2 offset = { 0,0 };

		virtual void Start() {};
		virtual void Update() {};

		Collider(GameObject* gameObject) :Component(gameObject) { isTrigger = false, isStatic = false, offset = AEVec2{ 0,0 }; };
		Collider() :Component(gameObject) { isTrigger = false, isStatic = false, offset = AEVec2{ 0,0 }; gameObject = nullptr; };
	};
			

	//AABB only
	class BoxCollider : public Collider 
	{
		private:
			AEVec2 min;
			AEVec2 max;
			AEVec2 extend;	//half of width and height 
			AEVec2& center { gameObject->transform.position };
			//indexes to cells they occupy
			std::vector<int> cell_indexes;
		public:
			RigidBody* rb;

			/*!*************************************************************************
			****
				\brief
					The boxcollider constructor
				\param gameObject
					The gameObject* use to construct the base collider class
					as a component
				\return

			****************************************************************************
			***/
			BoxCollider(GameObject* gameObject);

			/*!*************************************************************************
			****
				\brief
					The boxcollider copy constructor
				\param rhs
					The boxcollider to copy
				\return

			****************************************************************************
			***/
			BoxCollider(const BoxCollider& rhs) = default;

			/*!*************************************************************************
			****
				\brief
					The boxcollider copy assignment operator
				\param rhs
					The boxcollider to copy and assign
				\return

			****************************************************************************
			***/
			BoxCollider& operator=(const BoxCollider & rhs) = default;

			/*!*************************************************************************
			****
				\brief
					The start/init function that is called once for initalization
				\param none

				\return
					void
			****************************************************************************
			***/
			void Start();


			/*!*************************************************************************
			****
				\brief
					Gets the half width and half height of the boxcollider
					(ie. the extend of the collider)
				\param none
					
				\return
					The extend of the boxcollider
			****************************************************************************
			***/
			inline AEVec2 GetExtend() const
			{
				return extend;
			}

			/*!*************************************************************************
			****
				\brief
					Gets the center of the boxcollider
				\param none

				\return
					 The vector to the center of the boxcollider
			****************************************************************************
			***/
			inline AEVec2 GetCenter() const
			{
				return center;
			}

			/*!*************************************************************************
			****
				\brief
					Gets the aabb's min vector (btm left corner of the boxcollider)
				\param none

				\return
					 The vector to aabb's min vector
			****************************************************************************
			***/
			inline AEVec2 Min() const 
			{
				if (isStatic)
					return min;
				else
					return AEVec2{ center.x - extend.x , center.y - extend.y };
				
			}

			/*!*************************************************************************
			****
				\brief
					Gets the aabb's max vector (top right corner of the boxcollider)
				\param none

				\return
					 The vector to aabb's min vector
			****************************************************************************
			***/
			inline AEVec2 Max() const
			{
				if (isStatic)
					return max;
				else
					return AEVec2{ center.x + extend.x , center.y + extend.y };
				
			}

			/*!*************************************************************************
			****
				\brief
					Gets the boxcollider's height
				\param none

				\return
					The boxcollider's height
			****************************************************************************
			***/
			inline float GetHeight() const
			{
				return extend.y * 2.0f;
			}

			/*!*************************************************************************
			****
				\brief
					Gets the boxcollider's width
				\param none

				\return
					The boxcollider's width
			****************************************************************************
			***/
			inline float GetWidth() const
			{
				return extend.x * 2.0f;
			}

			

			
			//parition cell functions

			/*!*************************************************************************
			****
				\brief
					Get the collider's cell list
					(indexes to partition cells a collider occupy)
				\param none

				\return
					The reference to the cell list
			****************************************************************************
			***/
			const std::vector<int>& GetCellIndexes() const;


			/*!*************************************************************************
			****
				\brief
					Clears the partition cell list
					(indexes to partition cells a collider occupy)
				\param none

				\return
					void
			****************************************************************************
			***/
			void ClearCellList();

			/*!*************************************************************************
			****
				\brief
					Get the size of the cell list
					(indexes to partition cells a collider occupy)
				\param none

				\return
					Size of the cell list the collider contains
			****************************************************************************
			***/
			size_t GetCellListSize() const;

			/*!*************************************************************************
			****
				\brief
					Adds a cell to the cell list
					(indexes to partition cells a collider occupy)
				\param index
					The index of the collider the cell occupy
				\return
					Size of the cell list the collider contains
			****************************************************************************
			***/
			void AddToCellList(int);
 
	};
}
