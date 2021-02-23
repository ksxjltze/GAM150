#include "Collider.h"
#include "Physics.h"
using namespace StarBangBang;


BoxCollider::BoxCollider(AEVec2 _center, float width, float height) : Collider()
{
	extend = AEVec2{ width * 0.5f,height * 0.5f};
	min = AEVec2{_center.x - extend.x , _center.y - extend.y} ;
	max = AEVec2{ _center.x + extend.x , _center.y + extend.y };
	center = _center;
	
}
CircleCollider::CircleCollider(AEVec2 _center, float _rad ) : Collider()
{
	center = _center;
	radius = _rad;
}