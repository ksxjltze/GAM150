#include "Collider.h"

using namespace StarBangBang;

float BoxCollider::GetHeight()
{
    return extend.y * 2.0f;
}

 float BoxCollider::GetWidth()
{
    return extend.x * 2.0f;
}
BoxCollider::BoxCollider(GameObject* _go,AEVec2 _center, float width, float height)
{
	shape = ShapeType::Box;
	gameObject = _go;
	extend = AEVec2{ width * 0.5f,height * 0.5f};
	min = AEVec2{_center.x - extend.x , _center.y - extend.y} ;
	max = AEVec2{ _center.x + extend.x , _center.y + extend.y };;
	center = _center;
	
}
CircleCollider::CircleCollider(GameObject* _go, AEVec2 _center, float _rad )
{
	shape = ShapeType::Circle;
	gameObject = _go;
	center = _center;
	radius = _rad;
}