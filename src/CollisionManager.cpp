#include "CollisionManager.h"
#include <cmath>
#include <iostream>
#include <time.h>
using namespace StarBangBang;



CollisionData::CollisionData() 
	:pen_depth{ 0.0f }, col_normal{ 0.0f, 0.0f } {}

CollisionPair::CollisionPair(BoxCollider A, BoxCollider B, CollisionData data) : A{ A }, B{ B }, data()
{
}
namespace 
{
	std::queue<CollisionPair> resolveQueue;
	std::vector<BoxCollider> colliders;
}


void CalculateCollisionData(const BoxCollider& b1, const BoxCollider& b2, CollisionData& col)
{
	AEVec2 dist = AEVec2{ b2.center.x - b1.center.x , b2.center.y - b1.center.y };
	float x_intersect = b1.extend.x + b2.extend.x - fabs(dist.x);
	float y_intersect = b1.extend.y + b2.extend.y - fabs(dist.y);

	//Find the min intersect distance 
	if (x_intersect > y_intersect)
	{
		col.pen_depth = x_intersect;
		// means that b2 center on the left of b1 center 
		if (dist.x < 0)
			col.col_normal = AEVec2{ 1.0f,0.0f };
		else
			col.col_normal = AEVec2{ -1.0f,0.0f };
	}
	else
	{
		col.pen_depth = y_intersect;
		//means b2 center is below b1 center
		if (dist.y < 0)
			col.col_normal = AEVec2{ 0.0f, 1.0f };
		else
			col.col_normal = AEVec2{ 0.0f,-1.0f };

	}
	

}
//wip
void CollisionManager::ResolverUpdate()
{
	if (resolveQueue.empty())
		return;
	for (size_t i = 0; i < resolveQueue.size(); i++)
	{
		CollisionPair& pair = resolveQueue.front();
		CollisionManager::Resolve(pair.A,pair.B,pair.data);
		resolveQueue.pop();
	}
	
	
}
//wip
void CollisionManager::AddToResolveQueue(CollisionPair pair)
{
	resolveQueue.push(pair);
}
//check for static aabb
bool CollisionManager::StaticAABB_Check(const BoxCollider& A, const BoxCollider& B , CollisionData& data)
{

	if (A.isTrigger || B.isTrigger)
		return false;

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
	CalculateCollisionData(A,B,data);
	return true;
}

//check for moving aabbs
bool CollisionManager::Dynamic_AABB(const BoxCollider& A, const AEVec2& vel1,
	const BoxCollider& B, const AEVec2& vel2, CollisionData& data)
{ 
	if (StaticAABB_Check(A, B,data))
		return true;
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
	if (rVel_B.x > 0)
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
	if (rVel_B.y > 0)
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
	//no collision 
	if (t_first > t_last)
		return false;


	//Special case where either A and B static and not intersecting  OR 
	//They are moving at the same velocity and not colliding with each other in the first place
	return false;

	
}

bool CollisionManager::CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData& col)
{
	//axis = AEVec2Normalize();
	return AEVec2{ 0,0 };
}

bool CollisionManager::CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData* col)
{
	float r = c1.radius + c2.radius;
	float d = AEVec2SquareDistance(&c1.center, &c2.center);
	if (d > r * r)
		return false;
	//collided
	d = sqrtf(d);

	if (d != 0)
	{	
		col->pen_depth = r - d;
		col->col_normal = AEVec2{ (c2.center.x - c1.center.x) / d , (c2.center.y - c1.center.y) / d };
		return true;
	}
	//same circle center	
	col->pen_depth = c1.radius;
	col->col_normal = AEVec2{ 0, 1 };
	return true;
	
}

void CollisionManager::DebugCollider(BoxCollider b)
{
	
	AEVec2 size = AEVec2{ b.GetWidth(),b.GetHeight() };
	StarBangBang::DrawBoxWired(size, b.center);

}

void CollisionManager::DebugCollider(CircleCollider c, unsigned int sides)
{

	//AEGfxStart();

	float interval = roundf(2.0f * PI / sides / 10.0f) * 10.0f;
	for (unsigned int i = 0; i < sides; i++)
	{
		float radian  = interval * i;
		if (i + 1 < sides)
		{
			float x = c.radius * asinf(radian);
			float y = c.radius * acosf(radian);
			float x1 = c.radius * asinf(radian + interval);
			float y1 = c.radius * acosf(radian + interval);
			
			AEGfxLine(	c.center.x + x , c.center.y + y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
						c.center.x + x1, c.center.y + y1 , 0.0f ,0.0f ,0.0f ,0.0f ,1.0f
					
			);
		}
	}
	
	//AEGfxEnd();

}


