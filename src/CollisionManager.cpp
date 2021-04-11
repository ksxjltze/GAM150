/******************************************************************************/
/*!
\title		Captain Stealth
\file		CollisionManager.cpp
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the definition for CollisionManager.h
			Handles collision responds and detection

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/



#include "CollisionManager.h"
#include "BasicMeshShape.h"
#include "Grid.h"
#include <cmath>
#include "MessageBus.h"
#include "CollisionEvent.h"

using namespace StarBangBang;


const float EPILSION = 0.0001f;



/*!*************************************************************************
****
	\brief
		CollisionData constructor
	\param none
	
	\return
		void
****************************************************************************
***/
CollisionData::CollisionData()
	:pen_depth{ 0.0f }, col_normal{ 0.0f, 0.0f } {}


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
CollisionPair::CollisionPair(BoxCollider& A, BoxCollider& B, CollisionData data) : A{ A }, B{ B }, data{ data }
{
}

namespace
{
	//the partitioning grid
	PartitionGrid p_grid;
	
	//all colliders created
	std::vector<BoxCollider*> collider_list;

}


/*!*************************************************************************
****
	\brief
		Whether a point lies within the ray(line segment) 
	\param line
		The ray
	\param pt
		The point to check against
	\return
		Whether the param pt lies within the ray(line segment) 
****************************************************************************
***/
bool LineContainsPoint(const Ray& line, AEVec2 pt)
{
	
	AEVec2 p0 {line.start.x - pt.x , line.start.y - pt.y } ;
	AEVec2 p1 {line.end.x - pt.x , line.end.y - pt.y };


	float dotp0 = AEVec2DotProduct(&p0,&pt);
	float dotp1 = AEVec2DotProduct(&p0, &pt);

	//point within line
	if (dotp0 * dotp1 < 0)
		return true;
	return false;

}


/*!*************************************************************************
****
	\brief
		Calculate the orientation of the a point with respect
		to a line segment
	\param start
		The starting point of the line
	\param end
		The ending point of the line
	\param ptToTest
		The point use to calculate orientation
	\return
		0	- Collinear
		1	- Clockwise
		-1	- Anti-Clockwise
****************************************************************************
***/
int LineOrientation(AEVec2 start, AEVec2 end, AEVec2 ptToTest)
{
	//wedge product
	int ori = (int)roundf(
		(start.y - end.y) * (ptToTest.x - start.x) -
		(start.x - end.x) * (ptToTest.y - start.y)	);
	
	if (ori == 0) return 0;

	return (ori > 0) ? 1 : -1;
}

/*!*************************************************************************
****
	\brief
		Checks whether a ray intersects another ray
	\param l1
		The first ray
	\param l2
		The second ray

	\return
		Whether ray l1 intersects ray l2
		true if ray intersects each other
		otherwise returns false
****************************************************************************
***/

bool LineIntersect(const Ray& l1, const Ray& l2)
{

	int o1 = LineOrientation(l1.start, l1.end, l2.start);
	int o2 = LineOrientation(l1.start, l1.end, l2.end);
	int o3 = LineOrientation(l2.start, l2.end, l1.start);
	int o4 = LineOrientation(l2.start, l2.end, l1.end);

	//pairs of different orientation means line segment intersects
	if (o1 != o2 && o3 != o4)
		return true;

	// when points are collinear 
	// points are on the same line check if they are within the min and max bound of line
	if (o1 == 0 && LineContainsPoint(l1, l2.start) || o2 == 0 && LineContainsPoint(l1, l2.end)
		|| o3 == 0 && LineContainsPoint(l2, l1.start) || o4 == 0 && LineContainsPoint(l2, l1.end))
	{
		return true;
	}

	return false;
}


/*!*************************************************************************
****
	\brief
		Initialize function for collision manager
	\param none

	\return
		void
****************************************************************************
***/

void CollisionManager::CollisionManagerInit()
{
	p_grid.AllocateGrid();
}


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
BoxCollider* CollisionManager::LineCast(const Ray& ray, BoxCollider* ignore)
{
	const int c_sides = 4;
	for (BoxCollider* col : collider_list)
	{

		if (col == ignore)
			continue;

		//if ray starts inside the collider
		//intersect
		/*if (CollisionManager::ContainsPoint(*col, ray.start) || CollisionManager::ContainsPoint(*col, ray.end))
		{
			return col;
		}*/
		//box line segements
		Ray boxAxis[4] = {

				Ray{AEVec2{col->Min().x,col->Max().y },col->Max()},

				Ray{col->Max() , AEVec2{col->Max().x,col->Min().y }},

				Ray{AEVec2{col->Max().x,col->Min().y } , col->Min()},

				Ray{col->Min(),AEVec2{col->Min().x,col->Max().y }},
		};

		for (int i = 0; i < c_sides; ++i)
		{
			//intersect
			if (LineIntersect(boxAxis[i], ray))
			{
				return col;
			}

		}

	}
	//non intersect
	return nullptr;
}


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
void CollisionManager::ClearPartitionGridCell(int index)
{
	p_grid.ClearABucketCell(index);
}

/*!*************************************************************************
****
	\brief
		Clears all partition grid cell's bucket
	\return
		void

****************************************************************************
***/

void CollisionManager::ClearPartitionGridCells()
{
	p_grid.ClearAllBucketCell();
}


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
void StarBangBang::CollisionManager::RemoveCollider(Collider* pCollider)
{

	for (auto it = collider_list.begin(); it != collider_list.end(); it++)
	{
		if (*it == pCollider)
		{
			collider_list.erase(it);
			return;
		}
	}
}


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
BoxCollider* CollisionManager::CreateBoxColliderInstance(GameObject* gameObject, bool is_static)
{

	BoxCollider* c = new BoxCollider(gameObject);
	c->isStatic = is_static;
	collider_list.push_back(c);
	unsigned int index = (unsigned int)collider_list.size() - 1;

	std::vector<AEVec2> points;
	points.reserve(8);
	AEVec2 max = c->Max();
	AEVec2 min = c->Min();

	AEVec2 topR{ min.x, max.y };
	AEVec2 btmL{ max.x,min.y };
	AEVec2 v = min;
	//calcuate all the in between points 
	for (int y = 0; ; ++y)
	{
		if (v.x > max.x || v.y > max.y)
			break;
		for (int x = 0; ; ++x)
		{
			v = AEVec2{ c->Min().x + x * p_grid.GetCellSize() , c->Min().y + y * p_grid.GetCellSize() };

			if (v.x > max.x || v.y > max.y)
				break;

			points.push_back(v);

		}
	}
	points.push_back(max);
	points.push_back(topR);
	points.push_back(btmL);

	//PRINT("size:%zu \n" ,points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		int cellIndex = p_grid.GetHashCellIndex(points[i]);
		Cell& cell = p_grid.grid[cellIndex];
		cell.cellIndex = cellIndex;
		collider_list[index]->AddToCellList(cellIndex);
		cell.cell_colliders.insert(collider_list[index]);

		//PRINT("hash:%d \n", cellIndex);
	}
	return collider_list[index];
}


/*!*************************************************************************
****
	\brief
		Calculate the collision data when 2 collider intersects
	\param b1
		The first of the pair of intersect colliders
	\param b2
		The second of the pair of intersect colliders
	\param col
		The collision data reference to store calculation result
	\return
		void

****************************************************************************
***/
void CalculateCollisionData(const BoxCollider& b1, const BoxCollider& b2, CollisionData& col)
{
	AEVec2 dist = AEVec2{ b2.GetCenter().x - b1.GetCenter().x , b2.GetCenter().y - b1.GetCenter().y };

	float x_intersect = b1.GetExtend().x + b2.GetExtend().x - fabs(dist.x);
	float y_intersect = b1.GetExtend().y + b2.GetExtend().y - fabs(dist.y);

	//Find the min intersect distance 
	if (x_intersect > y_intersect)
	{
		col.pen_depth = y_intersect;
		// means that b2 center on the left of b1 center 
		if (dist.y < 0)
			col.col_normal = AEVec2{ 0.0f, -1.0f };
		else
			col.col_normal = AEVec2{ 0.0f, 1.0f };

	}
	else
	{
		col.pen_depth = x_intersect;
		//means b2 center is below b1 center
		if (dist.x < 0)
			col.col_normal = AEVec2{ -1.0f,0.0f };
		else
			col.col_normal = AEVec2{ 1.0f,0.0f };

	}


}


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
bool CollisionManager::ContainsPoint(const BoxCollider& box, AEVec2 pt)
{
	if (pt.x < box.Min().x || pt.y < box.Min().x)
		return false;
	if (pt.x > box.Max().x || pt.y > box.Max().y)
		return false;
	return true;

}


/*!*************************************************************************
****
	\brief
		Caculates all the parition cell a collider occupies
	\param c
		The boxcollider object reference
	\param list
		The vector cell* list to restore the result
	\return
		void
****************************************************************************
***/
void FetchAllColliderCells(const BoxCollider& c, std::vector<Cell*>& list)
{

	std::vector<AEVec2> points;
	points.reserve(8);
	AEVec2 max = c.Max();
	AEVec2 min = c.Min();

	AEVec2 topR{ min.x, max.y };
	AEVec2 btmL{ max.x,min.y };
	AEVec2 v = min;
	//calcuate all in between points 
	for (int y = 0; ; ++y)
	{
		if (v.x > max.x || v.y > max.y)
			break;
		for (int x = 0; ; ++x)
		{
			v = AEVec2{ c.Min().x + x * p_grid.GetCellSize() , c.Min().y + y * p_grid.GetCellSize() };

			if (v.x > max.x || v.y > max.y)
				break;

			points.push_back(v);

		}
	}
	points.push_back(max);
	points.push_back(topR);
	points.push_back(btmL);

	for (size_t i = 0; i < points.size(); ++i)
	{
		int cellIndex = p_grid.GetHashCellIndex(points[i]);

		assert(cellIndex < p_grid.GetBucketSize());
		Cell& cell = p_grid.grid[cellIndex];
		cell.cellIndex = cellIndex;
		list.push_back(&cell);
	}

}


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
void CollisionManager::RecalculateColliderCells(BoxCollider& col)
{
	//clear the cells collider occupies
	
	if (col.GetCellIndexes().size() > 0)
	{
		for (const int index : col.GetCellIndexes())
		{
			assert(index < p_grid.GetBucketSize());
			//PRINT("R_Index: %d\n", index);
			Cell& c = p_grid.grid[index];
			c.cell_colliders.erase(&col);
		}
		//clear all cell data from collider
		col.ClearCellList();
	}

	//update the new cells collider occupies
	std::vector<Cell*> cell_list;
	FetchAllColliderCells(col, cell_list);
	for (Cell* cell_ref : cell_list)
	{
		assert(cell_ref);
		//if (!cell_ref)
		//	continue;

		cell_ref->cell_colliders.insert(&col);
		col.AddToCellList(cell_ref->cellIndex);

	}


}

/*!*************************************************************************
****
	\brief
		Resolve the velocity of 2 rigibodies
	\param pair
		The collisionpair reference containing
		the collided colliders and data
	\return
		void
****************************************************************************
***/
void ResolveVelocity(const CollisionPair& pair)
{
	AEVec2 normal = pair.data.col_normal;
	AEVec2 relVel = AEVec2{ pair.B.rb->velocity.x - pair.A.rb->velocity.x
							, pair.B.rb->velocity.y - pair.A.rb->velocity.y };

	float dotVelScale = AEVec2DotProduct(&relVel, &normal);
	//towards same direction as resolving normal 
	if (dotVelScale > 0)
		return;

	float scale = (1.0f + bounciness) * dotVelScale;
	float total = pair.A.rb->inv_mass() + pair.B.rb->inv_mass();

	if (total > 0)
	{
		scale /= total;

		// Apply impulse
		AEVec2 impulse{ normal.x * scale  , normal.y * scale };

		//check for accounting static obejcts with no rb
		pair.A.rb->AddVelocity(impulse, pair.A.rb->inv_mass());
		pair.B.rb->AddVelocity(impulse, -pair.B.rb->inv_mass());
	}
}

/*!*************************************************************************
****
	\brief
		Resolve penetration of intersecting collider pairs
	\param pair
		The collisionpair reference containing
		the collided colliders and data
	\return
		void
****************************************************************************
***/

void ResolvePenetration(const CollisionPair& pair)
{
	float total = pair.A.rb->inv_mass() + pair.B.rb->inv_mass();

	if (total <= 0)
		return;
	//negate small values to prevent jitter
	f32 xMax = max(pair.data.pen_depth - 0.1f, 0.0f);
	f32 yMax = max(pair.data.pen_depth - 0.1f, 0.0f);

	//might be helpful to compensate IEEE rounding error (we might not need cuz no constant gravity i think)
	const float additional = 1.3f;
	//position correction impulse for penetration depth 
	AEVec2 corr = AEVec2{ additional * xMax / total * pair.data.col_normal.x , additional * yMax / total * pair.data.col_normal.y };

	pair.A.rb->AddInstantVelocity(corr, -pair.A.rb->inv_mass());

	pair.B.rb->AddInstantVelocity(corr, pair.B.rb->inv_mass());


}


/*!*************************************************************************
****
	\brief
		Reset/free the collision manager data
	\param none
	
	\return
		void
****************************************************************************
***/
void StarBangBang::CollisionManager::Free()
{
	collider_list.clear();
	CollisionManager::ClearPartitionGridCells();
}

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
void CollisionManager::ResolverUpdate()
{
	/*static size_t collision_check = 0;
	static float timer = 5.0f;*/
	//non-partition 
	//for (BoxCollider* col : collider_list)
	//{

	//	for (BoxCollider* col2 : collider_list)
	//	{
	//		assert(col2);

	//		if (col == col2)
	//			continue;
	//		CollisionData data;

	//		//if both have rb use dynamic collision
	//		if (col->rb && col2->rb)
	//		{
	//			if (Dynamic_AABB(*col, col->rb->velocity, *col2, col2->rb->velocity))
	//			{
	//				if (col->isTrigger || col2->isTrigger)
	//				{
	//					Event collisionEvent;
	//					collisionEvent.id = EventId::COLLISION;
	//					collisionEvent.context = std::pair<Collider*, Collider*>(col, col2);
	//					MessageBus::Notify(collisionEvent);
	//					continue;
	//				}

	//				CalculateCollisionData(*col, *col2, data);
	//				CollisionPair p{ *col,*col2, data };
	//				ResolveVelocity(p);
	//				ResolvePenetration(p);
	//			}

	//		}
	//		//if (timer > 0)
	//		//{
	//		//	++collision_check;
	//		//}
	//	}

	//}


#pragma region Partition
	
	//paritition 
	for (BoxCollider* col : collider_list)
	{
		assert(col);

		if(col->rb && col->rb->isKinematic())
			RecalculateColliderCells(*col);
		//printf("%zu\n", collider_list.size());
		if (col->GetCellListSize() > 0)
		{
			for (const int index : col->GetCellIndexes())
			{
				//PRINT("C_Index: %d\n", index);
				assert(index < p_grid.GetBucketSize());

				Cell& c = p_grid.grid[index];
				for (BoxCollider* col2 : c.cell_colliders)
				{
					assert(col2);

					if (!col->gameObject->active || !col2->gameObject->active)
						continue;
				
					//assert(index < c.cell_collider);
					if (col2 == col)
						continue;
					CollisionData data;

					assert(col2->rb);
					if (col->rb && col2->rb)
					{

						if (col->isStatic && col2->isStatic)
							continue;

						if (Dynamic_AABB(*col, col->rb->velocity, *col2, col2->rb->velocity))
						{
							
							if (col->isTrigger || col2->isTrigger)
							{
								Event e{ EventId::COLLISION, CollisionEvent{col, col2 } };
								MessageBus::Notify(e);
								continue;
							}

							if (col->gameObject->name == "Player" || col->gameObject->name == "Client")
							{
								Event e{ EventId::PLAYER_COLLISION, CollisionEvent{col, col2} };
								MessageBus::Notify(e);
							}

							CalculateCollisionData(*col, *col2, data);
							CollisionPair p{ *col,*col2, data };
							ResolveVelocity(p);
							ResolvePenetration(p);
						}

					}
				
					/*if (timer > 0)
					{
						++collision_check;
					}*/

				}

			}
		}

	}
	//std::cout << collision_check << std::endl;
	//timer -= AEFrameRateControllerGetFrameTime();
#pragma endregion

	//drawing of colliders
	/*if (!debug)
		return;

	for (BoxCollider* col : collider_list)
	{
		assert(col);
		if (col->rb->isKinematic())
			DebugCollider(*col, Red);
		else
			DebugCollider(*col, Green);
	}*/

}

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

void StarBangBang::CollisionManager::SetDebugVisible(bool b)
{
	debug = b;
}

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
bool CollisionManager::StaticAABB_Check(const BoxCollider& A, const BoxCollider& B)
{

	//if (A.isTrigger || B.isTrigger)
	//	return false;

	//A is outside B bounding box
	if (A.Min().x > B.Max().x || A.Min().y > B.Max().y)
	{
		return false;
	}
	//B is outside A bounding box
	if (B.Min().x > A.Max().x || B.Min().y > A.Max().y)
	{
		return false;
	}
	
	return true;
}

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
bool CollisionManager::Dynamic_AABB(const BoxCollider& A, const AEVec2& vel1,
	const BoxCollider& B, const AEVec2& vel2)
{

	if (StaticAABB_Check(A, B))
	{
		return true;

	}

	//first collision time //collision exit time
	float t_first = 0, t_last = (float)AEFrameRateControllerGetFrameTime();
	//B relative velocity to A (where A = aabb1,vel1 , B = aabb2 , vel2)

	AEVec2 rVel_B{ vel2.x - vel1.x,vel2.y - vel1.y };

	//x-axis
	//B moving left
	if (rVel_B.x < 0)
	{
		//A is on the right
		if (A.Min().x > B.Max().x)
			return false;
		//A is on the left
		if (A.Max().x < B.Min().x)
		{
			//curr collision time
			float f_temp = (A.Max().x - B.Min().x) / rVel_B.x;
			//take the max time compared to last frame
			t_first = max(f_temp, t_first);

		}
		//the frame where B is exiting A
		if (A.Min().x < B.Max().x)
		{
			//last collision time
			float l_temp = (A.Min().x - B.Max().x) / rVel_B.x;
			//take the min time compared to last frame
			t_last = min(l_temp, t_last);
		}


	}
	//B moving right
	else if (rVel_B.x > 0)
	{
		//A is on the left
		if (A.Max().x < B.Min().x)
			return false;
		//A is on the right
		if (A.Min().x > B.Max().x)
		{
			float f_temp = (A.Min().x - B.Max().x) / rVel_B.x;
			t_first = max(f_temp, t_first);

		}
		//the frame where B is exiting A
		if (A.Max().x > B.Min().x)
		{
			float l_temp = (A.Max().x - B.Min().x) / rVel_B.x;
			t_last = min(l_temp, t_last);
		}

	}
	else
	{
		return false;
	}
	//no collision 
	if (t_first > t_last)
		return false;
	//y-axis
	//B moving down
	if (rVel_B.y < 0)
	{
		//A is on top
		if (A.Min().y > B.Max().y)
			return false;
		//A is on the bottom
		if (A.Max().y < B.Min().y)
		{
			float f_temp = (A.Max().y - B.Min().y) / rVel_B.y;
			t_first = max(f_temp, t_first);

		}
		//the frame where B is exiting A
		if (A.Min().y < B.Max().y)
		{
			float l_temp = (A.Min().y - B.Max().y) / rVel_B.y;
			t_last = min(l_temp, t_last);
		}

	}
	//B moving up
	else if (rVel_B.y > 0)
	{
		//A is on the bottom
		if (A.Max().y < B.Min().y)
			return false;
		//A is on the top
		if (A.Min().y > B.Max().y)
		{
			float f_temp = (A.Min().y - B.Max().y) / rVel_B.y;
			t_first = max(f_temp, t_first);

		}
		//the frame where B is exiting A
		if (A.Min().y < B.Max().y)
		{
			float l_temp = (A.Max().y - B.Min().y) / rVel_B.y;
			t_last = min(l_temp, t_last);
		}

	}
	else
	{
		return false;
	}
	//no collision 
	if (t_first > t_last)
		return false;

	return true;


}


/*!*************************************************************************
****
	\brief
		Draw a boxcollider for debugging
	\param c
		The boxcollider to draw
	\param color
		The color used to render the boxcollider
	\return
		void
****************************************************************************
***/
void CollisionManager::DebugCollider(BoxCollider b, Color c)
{

	AEVec2 size = AEVec2{ b.GetWidth(),b.GetHeight() };
	StarBangBang::DrawBoxWired(size, b.GetCenter(), c);

}





