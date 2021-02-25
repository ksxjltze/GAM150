#include "Collider.h"
<<<<<<< HEAD
#include "Physics.h"
using namespace StarBangBang;

BoxCollider::BoxCollider(GameObject* _go,AEVec2 _center, float width, float height) : Collider()
{
	//gameObject = _go;
=======

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
>>>>>>> Yg
	extend = AEVec2{ width * 0.5f,height * 0.5f};
	min = AEVec2{_center.x - extend.x , _center.y - extend.y} ;
	max = AEVec2{ _center.x + extend.x , _center.y + extend.y };;
	center = _center;
	
}
<<<<<<< HEAD
CircleCollider::CircleCollider(GameObject* _go, AEVec2 _center, float _rad ) : Collider()
{
	//gameObject = _go;
=======
CircleCollider::CircleCollider(GameObject* _go, AEVec2 _center, float _rad )
{
	shape = ShapeType::Circle;
	gameObject = _go;
>>>>>>> Yg
	center = _center;
	radius = _rad;
}