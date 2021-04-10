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

		CollisionData();

	};

	//A structure of a collision pair
	struct CollisionPair
	{
	public:
		
		BoxCollider& A ;
		BoxCollider& B;
		CollisionData data;
		CollisionPair(BoxCollider& A, BoxCollider& B, CollisionData data);
	
	};



	namespace CollisionManager
	{
		void Free();
		void AddToColliders(BoxCollider);
		void ResolverUpdate();
		void AddToResolveQueue(CollisionPair);

		void SetDebugVisible(bool);

		bool StaticAABB_Check(const BoxCollider& A, const BoxCollider& B);
		bool Dynamic_AABB(const BoxCollider& A, const AEVec2& vel1, const BoxCollider& B, const AEVec2& vel2);
	
		void RecalculateColliderCells(BoxCollider&);

		void DebugCollider(BoxCollider b, Color c );

	
		void ClearPartitionGridCell(int index);


		BoxCollider* LineCast(const Ray& ray, BoxCollider* ignore);

		


		void ClearPartitionGridCells();

		void RemoveCollider(Collider* pCollider);


		BoxCollider* CreateBoxColliderInstance(GameObject* gameObject,bool is_static = true);

		bool ContainsPoint(const BoxCollider& box,AEVec2 pt);
		static bool debug = false;

		

	}
	
}

