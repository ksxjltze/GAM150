/******************************************************************************/
/*!
\title		Captain Stealth
\file		Collider.cpp
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the definition for Collider.h
			Contains collider class and functions
			for collision

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#include "Collider.h"
#include "CollisionManager.h"
#include "Physics.h"
using namespace StarBangBang;

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
void BoxCollider::ClearCellList()
{
	cell_indexes.clear();
}

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
size_t StarBangBang::BoxCollider::GetCellListSize() const
{
	return cell_indexes.size();
}


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
void BoxCollider::AddToCellList(int index)
{
	for (const int v : cell_indexes)
	{
		if (v == index)
			return;
	}
	cell_indexes.push_back(index);

}

/*!*************************************************************************
****
	\brief
		The start/init function that is called once for initalization
	\param none
		
	\return
		void
****************************************************************************
***/
void StarBangBang::BoxCollider::Start()
{
	rb = gameObject->GetComponent<RigidBody>();

}


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
const std::vector<int>& BoxCollider::GetCellIndexes() const
{
	return cell_indexes;
}


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

StarBangBang::BoxCollider::BoxCollider(GameObject* gameObject) : Collider(gameObject)
{
	float width = gameObject->transform.scale.x * GRAPHICS::MESH_WIDTH;
	float height = gameObject->transform.scale.y * GRAPHICS::MESH_HEIGHT;
	AEVec2 _center = gameObject->transform.position;

	extend = AEVec2{ width * 0.5f,height * 0.5f };
	min = AEVec2{ _center.x - extend.x , _center.y - extend.y };
	max = AEVec2{ _center.x + extend.x , _center.y + extend.y };

	rb = gameObject->GetComponent<RigidBody>();

}




