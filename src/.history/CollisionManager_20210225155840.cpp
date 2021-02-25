#include "CollisionManager.h"
#include <cmath>
#include <iostream>
#include "BasicMeshShape.h"
#include <time.h>
using namespace StarBangBang;
const float bounciness = 1.25f;

AEVec2 CollisionManager::ProjectOnToAxis(AEVec2 v, AEVec2 axis)
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
		col.pen_depth = r - d;
		//normalize normal with calculated distance
		col.col_normal = AEVec2{ (c2.center.x - c1.center.x) / d , (c2.center.y - c1.center.y) / d };
		return true;
	}
	//same circle center	
	col.pen_depth = c1.radius > c2.radius ? c2.radius: c1.radius;
	col.col_normal = AEVec2{ 0, 1 };
	return true;
	
}
bool CollisionManager::AABBvsAABB(BoxCollider b1, BoxCollider b2, CollisionData& col)
{
	//both is trigger no collision
	if (b1.isTrigger && b1.isTrigger)
		return false;
	

	AEVec2 dist = AEVec2{ b2.center.x - b1.center.x , b2.center.y - b1.center.y };
	float x_intersect = b1.extend.x + b2.extend.x - fabs(dist.x);
	float y_intersect = b1.extend.y + b2.extend.y - fabs(dist.y);

	//intersect
	if (x_intersect > 0)
	{
		if (y_intersect > 0)
		{
			//Find the min intersect distance 
			if (x_intersect > y_intersect)
			{
				col.pen_depth = x_intersect ;
				// means that b2 center on the left of b1 center (as center.x is b2-b1)
				if (dist.x < 0)
					col.col_normal = AEVec2{ 1.0f,0.0f };
				else
					col.col_normal = AEVec2{ -1.0f,0.0f };

				return true;
			}
			else
			{
				col.pen_depth = y_intersect ;
				//means b2 center is below b1 center
				if (dist.y < 0)
					col.col_normal = AEVec2{ 0.0f, 1.0f };
				else
					col.col_normal = AEVec2{ 0.0f,-1.0f };

				return true;
			}
		}
			
	}

	return false;

}


void CollisionManager::DebugCollider(BoxCollider b)
{
	
	AEVec2 size = AEVec2{ b.GetWidth(),b.GetHeight() };
	StarBangBang::DrawBox(size, b.center);

}

void CollisionManager::DebugCollider(CircleCollider c)
{

	StarBangBang::DrawCircle(c.radius,c.center);
		col->pen_depth = r - d;
		col->col_normal = AEVec2{ (c2.center.x - c1.center.x) / d , (c2.center.y - c1.center.y) / d };
		return true;
	}
	//same circle center	
	col->pen_depth = c1.radius;
	col->col_normal = AEVec2{ 0, 1 };
	return true;
	
}
bool CollisionManager::AABBvsAABB(BoxCollider b1, BoxCollider b2, CollisionData* col)
{
	AEVec2 dist = AEVec2{ b2.center.x - b1.center.x , b2.center.y - b1.center.y };
	float x_intersect = b1.extend.x + b2.extend.x - fabs(dist.x);
	float y_intersect = b1.extend.y + b2.extend.y - fabs(dist.y);
	//same box center
	if (dist.x == 0 && dist.y == 0)
	{
		col->col_normal = AEVec2{ -1,0 };
		col->pen_depth = b1.extend.x;
		return true;
	}
	//intersect on both axis || only x-axis || only y-axis
	if (x_intersect > 0 && y_intersect > 0 || x_intersect > 0 || y_intersect > 0)
	{
		//Find the min intersect distance 
		if (x_intersect < y_intersect || x_intersect > 0)
		{
			col->pen_depth = x_intersect;
			// means that b2 center on the left of b1 center (as center.x is b2-b1)
			if (dist.x < 0)
				col->col_normal = AEVec2{ -1.0f,0.0f };
			else
				col->col_normal = AEVec2{ 1.0f,0.0f };

			return true;
		}
		if (x_intersect > y_intersect || y_intersect > 0)
		{
			col->pen_depth = y_intersect;
			//means b2 center is below b1 center
			if (dist.y < 0)
				col->col_normal = AEVec2{ 0.0f, -1.0f };
			else
				col->col_normal = AEVec2{ 0.0f,1.0f };

			return true;
		}
	
		return false;
		
	}

	/*if (b2.min.x - b1.max.x > 0 || b2.min.y - b1.max.y > 0)
	{
		col.collide = false;
	}
	if (b1.min.x - b2.max.x > 0 || b1.min.y - b2.max.y > 0)
	{
		col.collide = false;
	}*/
}

void CollisionManager::Resolve_CirclevsCircle(CircleCollider c1, CircleCollider c2 ,  CollisionData* const col)
{
	if (c1.isTrigger || c2.isTrigger)
		return;
	
	AEVec2 resolveForce;
	if (col)
	{
		float scale = bounciness * col->pen_depth;
		AEVec2Scale(&resolveForce, &col->col_normal, scale);
		//movement force // (reminder)should over be dt 
		AEVec2 temp = c1.center;
		AEVec2 temp1 = c2.center;
		//push c1
		AEVec2Add(&c1.center, &temp, &resolveForce);
		//invert direction
		resolveForce = AEVec2{ resolveForce.x * -1.0f,resolveForce.y * -1.0f };
		//push c2
		AEVec2Add(&c2.center, &temp1, &resolveForce);
	}
	
}
void CollisionManager::Resolve_BoxvsBox(BoxCollider b1, BoxCollider b2, CollisionData* const col)
{
	if (b1.isTrigger || b2.isTrigger)
		return;
	AEVec2 resolveForce;
	if (col)
	{
		float scale = bounciness * col->pen_depth;
		AEVec2Scale(&resolveForce, &col->col_normal, scale);
		//movement force // (reminder)should over be dt 
		AEVec2 temp = b1.center;
		AEVec2 temp1 = b2.center;
		//push box1
		AEVec2Add(&b1.center, &temp, &resolveForce);
		//invert direction
		resolveForce = AEVec2{ resolveForce.x * -1.0f,resolveForce.y * -1.0f };
		//push box2
		AEVec2Add(&b2.center, &temp1, &resolveForce);
	}
}
void CollisionManager::DebugCollider(BoxCollider b)
{
	
	//AEGfxStart();
	AEGfxBox(	b.center.x, b.center.y, 0.0f, b.GetWidth(), 
				b.GetHeight(), 0.0f, 0x00FF00, 0x00FF00);
	//AEGfxEnd();
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

/*bool CollisionManager::SATBox(BoxCollider b1, BoxCollider b2)
{
	bool intersect;
	AEVec2 axis[6];
	AEVec2Sub(&axis[0], &b1.points[1], &b1.points[0]);
	AEVec2Sub(&axis[1], &b1.points[1], &b1.points[2]);
	AEVec2Sub(&axis[2], &b2.points[1], &b2.points[0]);
	AEVec2Sub(&axis[3], &b2.points[2], &b2.points[1]);
	AEVec2Sub(&axis[4], &b2.points[3], &b2.points[2]);
	AEVec2Sub(&axis[5], &b2.points[3], &b2.points[0]);
	unsigned int currAxis = 0;

	float b1_min = 10000000.0f, b1_max = -10000000.0f;
	float b2_min = 10000000.0f, b2_max = -10000000.0f;

	while (currAxis < 7)
	{
		//reset value for another test
		b1_min = 10000000.0f;
		b1_max = -10000000.0f;
		b2_min = 10000000.0f;
		b2_max = -10000000.0f;
		for (int i = 0; i < 4; i++)
		{
			AEVec2 proj_B1 = ProjectOnToAxis(b1.points[i], axis[currAxis]);
			float b1_temp = AEVec2DotProduct(&proj_B1, &axis[currAxis]);

			//keep track of min and max value on axis for each box corners
			if (b1_temp < b1_min)
			{
				b1_min = b1_temp;
			}
			if (b1_temp > b1_max)
			{
				b1_max = b1_temp;
			}
			AEVec2 proj_B2 = ProjectOnToAxis(b2.points[i], axis[currAxis]);
			float b2_temp = AEVec2DotProduct(&proj_B2, &axis[currAxis]);
			//keep track of min and max value on axis for each box corners
			if (b2_temp < b2_min)
			{
				b2_min = b2_temp;
			}
			if (b2_temp > b2_max)
			{
				b2_max = b2_temp;
			}

		}
		//failed to intersect
		if (b1_max < b2_min || b2_max < b1_min)
		{
			return 0;
		}
		else
		{
			currAxis++;
			intersect = 1;
		}
	}


	return intersect;
}*/


