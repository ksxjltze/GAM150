/******************************************************************************/
/*!
\title		Captain Stealth
\file		CollisionManager.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the declaration for CollisionManager.cpp
			Handles collision responds and detection

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#pragma once
#include "Collider.h"
namespace StarBangBang
{
	
	class Color;

	//additional resolve force multiplier
	//bounciness
	const float bounciness = 0.1f;
	
	class PartitionGrid;

	struct CollisionData
	{
	public:
		float pen_depth = 0.0f;
		AEVec2 col_normal;

		/*!*************************************************************************
		****
			\brief
				CollisionData constructor
			\param none

			\return
				void
		****************************************************************************
		***/
		CollisionData();

	};

	//A structure of a collision pair
	struct CollisionPair
	{
	public:
		
		BoxCollider& A ;
		BoxCollider& B;
		CollisionData data;

		/*!*************************************************************************
		****
			\brief
				CollisionPair constructor
			\param A
				The first collider
			\param B
				The second collider
			\param data
				The resulting collision data
			\return
				void
		****************************************************************************
		***/
		CollisionPair(BoxCollider& A, BoxCollider& B, CollisionData data);
	
	};



	namespace CollisionManager
	{
		static bool debug = false;

		/*!*************************************************************************
		****
			\brief
				Reset/free the collision manager data
			\param none

			\return
				void
		****************************************************************************
		***/
		void Free();


		void AddToColliders(BoxCollider);

		/*!*************************************************************************
		****
			\brief
				The update function of the manager
				Handles collisoin checks and resolving
				Recalculate moved colliders for partition grid
			\param none

			\return
				void
		****************************************************************************
		***/
		void ResolverUpdate();


		/*!*************************************************************************
		****
			\brief
				Sets the grid's visiblity to param b
			\param b
				The boolean value
			\return
				void
		****************************************************************************
		***/
		void SetDebugVisible(bool);


		/*!*************************************************************************
		****
			\brief
				Checks for static boxcollider(aabb) collision
			\param A
				First collider reference
			\param B
				Second collider reference
			\return
				true if the boxcollider intersects
				otherwise false
		****************************************************************************
		***/
		bool StaticAABB_Check(const BoxCollider& A, const BoxCollider& B);


		/*!*************************************************************************
		****
			\brief
				Checks for dynamic moving boxcollider (aabb) collision
			\param A
				First collider reference
			\param vel1
				Velocity of first collider A
			\param B
				Second collider reference
			\param vel2
				Velocity of second collider B
			\return
				true if the boxcollider intersects
				otherwise false
		****************************************************************************
		***/
		bool Dynamic_AABB(const BoxCollider& A, const AEVec2& vel1, const BoxCollider& B, const AEVec2& vel2);
		


		/*!*************************************************************************
		****
			\brief
				Recalculates a collider's partitioning cells
				when it moves
			\param col
				The boxcollider object reference
			\return
				void
		****************************************************************************
		***/
		void RecalculateColliderCells(BoxCollider&);

		void DebugCollider(BoxCollider b, Color c );

		/*!*************************************************************************
		****
			\brief
				Clears a partition grid cell's bucket
			\param index
				The index to the bucket cell

			\return
				void

		****************************************************************************
		***/
		void ClearPartitionGridCell(int index);



		/*!*************************************************************************
		****
			\brief
				Cast a ray and returns the collider it intersects
			\param ray
				The ray object
			\param ignore
				The boxcollider* to ignore

			\return
				returns the boxcollider* that the ray intersects
				nullptr if no intersection
		****************************************************************************
		***/
		BoxCollider* LineCast(const Ray& ray, BoxCollider* ignore);

		

		/*!*************************************************************************
		****
			\brief
				Clears all partition grid cell's bucket
			\return
				void

		****************************************************************************
		***/
		void ClearPartitionGridCells();



		/*!*************************************************************************
		****
			\brief
				Removes a collider for the collsion list
			\param pCollider
				The ptr to the collider to remove

			\return
				void
		****************************************************************************
		***/
		void RemoveCollider(Collider* pCollider);

		/*!*************************************************************************
		****
			\brief
				Creates a box collider instance
			\param gameObject
				The gameObject* to initialize a component

			\return
				The boxcollider ptr created

		****************************************************************************
		***/
		BoxCollider* CreateBoxColliderInstance(GameObject* gameObject,bool is_static = true);


		/*!*************************************************************************
		****
			\brief
				Whether a boxcollider contains a point
			\param box
				The boxcollider object reference
			\param pt
				The point to test
			\return
				true if box contains the point
				otherwise return false

		****************************************************************************
		***/
		bool ContainsPoint(const BoxCollider& box,AEVec2 pt);
	

	}
	
}

