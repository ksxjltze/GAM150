#include "CollisionManager.h"
#include <cmath>
#include <iostream>
using namespace StarBangBang;

const float bounciness = 1.25f;
unsigned int c_render_size = 20; // circle points render amount
AEVec2 CollisionManager::ProjectOnToAxis(AEVec2 v, AEVec2 axis)
{
	//axis = AEVec2Normalize();
	return AEVec2{ 0,0 };
}

bool CollisionManager::CircleVsCircle(CircleCollider c1, CircleCollider c2 , CollisionData* collision)
{
	float r = c1.radius + c2.radius;
	float d = AEVec2SquareDistance(&c1.center, &c2.center);
	if (d  > r * r) return false;
	//collided
	d = sqrtf(d);
	if (d != 0)
	{
		if (collision)
		{
			collision->pen_depth = r - d;
			collision->col_normal = AEVec2{ (c2.center.x - c1.center.x) / d , (c2.center.y - c1.center.y) / d };	
			
		}
		else
		{
			collision = nullptr;
			std::cout << "Error: CollisionData is nullptr" << "\n";
		}
				
		return true;
	}
	else //circle center is on top of each other
	{
		if (collision)
		{
			collision->pen_depth = c1.radius;
			collision->col_normal = AEVec2{ 0, 1 };
			
		}
		else
		{
			collision = nullptr;
			std::cout << "Error: CollisionData is nullptr" << "\n";
		}
		
		return true;
	}
}
bool CollisionManager::AABBvsAABB(BoxCollider b1, BoxCollider b2)
{
	if (b2.min.x - b1.max.x > 0 || b2.min.y - b1.max.y > 0)
	{
		return false;
	}
	if (b1.min.x - b2.max.x > 0 || b1.min.y - b2.max.y > 0)
	{
		return false;
	}
	return true;
}

void CollisionManager::Resolve_CirclevsCircle(CircleCollider c1, CircleCollider c2 , CollisionData col)
{
	if (c1.isTrigger || c2.isTrigger)
		return;
	
	AEVec2 resolveForce;
	float scale = bounciness * col.pen_depth;
	AEVec2Scale(&resolveForce, &col.col_normal, scale);
	//movement force // (reminder)should over be dt 
	AEVec2 temp = c1.center;
	AEVec2Add(&c1.center, &temp, &resolveForce);
}
void CollisionManager::DebugCollider(BoxCollider c)
{
	
}
void CollisionManager::DebugCollider(CircleCollider c)
{
	AEGfxStart();
	float inc_angle = round(2.0f * PI / c_render_size * 10.0f)/10.0f;
	float vert_txt = roundf (1.0f / c_render_size * 10.0f )/10.0f;
	AEVec2 start = AEVec2{ c.center.x , c.center.y * c.radius };
	AEVec2 vresult;
	AEMtx33 rot; 
	AEGfxVertexList* verts;
	AEGfxVertexAdd(start.x, start.y, 0x00FF00, 0.0f, inc_angle);
	for (int i = 1; i < c_render_size; i++)
	{
		AEMtx33Rot(&rot, inc_angle * i);
		AEMtx33MultVec(&vresult,&rot , &start);
		//AEGfxVertexAdd(c.center.x + vresult.x, c.center.y + vresult.y, 0xFF0000, , )
	}
	//AEGfxMeshDraw
	//AEGfxEnd();

	(c.center.x);
}
void StarBangBang::CollisionManager::Resolve_BoxvsBox(BoxCollider b1, BoxCollider b2, CollisionData col)
{
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


