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
BoxCollider::BoxCollider(AEVec2 _min, AEVec2 _max, AEVec2 _center, float width = 1.0f, float height = 1.0f)
{
	shape = ShapeType::Box;
	min = _min;
	max = _max;
	center = _center;
	extend = AEVec2{ width,height };
}
CircleCollider::CircleCollider(GameObject* _go, AEVec2 _center, float _rad = 1.0f)
{
	shape = ShapeType::Circle;
	gameObject = _go;
	center = _center;
	radius = _rad;
}