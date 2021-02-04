#include "Collider.h"
#include "Physics.h"
using namespace StarBangBang;

BoxCollider::BoxCollider(GameObject* _go,AEVec2 _center, float width, float height) : Collider()
{
	//gameObject = _go;
	extend = AEVec2{ width * 0.5f,height * 0.5f};
	min = AEVec2{_center.x - extend.x , _center.y - extend.y} ;
	max = AEVec2{ _center.x + extend.x , _center.y + extend.y };;
	center = _center;
	
}
CircleCollider::CircleCollider(GameObject* _go, AEVec2 _center, float _rad ) : Collider()
{
	//gameObject = _go;
	center = _center;
	radius = _rad;
}