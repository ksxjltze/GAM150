#include "Collider.h"
#include "CollisionManager.h"

using namespace StarBangBang;



void BoxCollider::SetCenter(float x, float y)
{
	center.x = x;
	center.y = y;
	CollisionManager::RecalculateColliderCells(*this);
}
void BoxCollider::Translate(float x , float y)
{
	center.x += x;
	center.y += y;
	CollisionManager::RecalculateColliderCells(*this);
}

void BoxCollider::ClearCellList()
{
	cell_indexes.clear();
}

size_t StarBangBang::BoxCollider::GetCellListSize() const
{
	return cell_indexes.size();
}

void BoxCollider::AddToCellList(int index)
{
	for (const int v : cell_indexes)
	{
		if (v == index)
			return;
	}
	cell_indexes.push_back(index);
	
}

const std::vector<int>& BoxCollider::GetCellIndexes() const
{
	return cell_indexes;
}

StarBangBang::BoxCollider::BoxCollider(GameObject* gameObject) : Collider(gameObject)
{
	float width = gameObject->transform.scale.x * GRAPHICS::MESH_WIDTH;
	float height = gameObject->transform.scale.y * GRAPHICS::MESH_HEIGHT;
	AEVec2 _center = gameObject->transform.position;

	extend = AEVec2{ width * 0.5f,height * 0.5f };
	min = AEVec2{ _center.x - extend.x , _center.y - extend.y };
	max = AEVec2{ _center.x + extend.x , _center.y + extend.y };

	//center = _center;
	//CollisionManager::AddToColliders(*this);
}

//BoxCollider::BoxCollider(AEVec2 min, AEVec2 max,bool isStatic) 
//{
//	this->min = min;
//	this->max = max;
//	this->isStatic = isStatic;
//	float width = max.x - min.x;
//	float height = max.y - min.y;
//	extend = AEVec2{ width * 0.5f,height * 0.5f };
//	center = AEVec2{min.x + extend.x, min.y + extend.y};
//	//CollisionManager::AddToColliders(*this);
//}
//
//BoxCollider::BoxCollider(AEVec2 _center, bool _isStatic , float width, float height) : Collider()
//{
//	extend = AEVec2{ width * 0.5f,height * 0.5f};
//	min = AEVec2{_center.x - extend.x , _center.y - extend.y} ;
//	max = AEVec2{ _center.x + extend.x , _center.y + extend.y };
//	isStatic = _isStatic;
//	center = _center;
//	//CollisionManager::AddToColliders(*this);
//	
//}



CircleCollider::CircleCollider(AEVec2 _center, float _rad ) : Collider()
{
	center = _center;
	radius = _rad;
}

void CircleCollider::SetCenter(float x, float y)
{
	center.x = x;
	center.y = y;
}

void CircleCollider::Translate(float x, float y)
{
	center.x += x;
	center.y += y;
}

void StarBangBang::BoxCollider::Update()
{
	PRINT("TEST");
}

void StarBangBang::BoxCollider::LateUpdate()
{

}

void StarBangBang::CircleCollider::Update()
{
	//if (gameObject)
	//{
	//	AEVec2 pos = gameObject->GetPos();
	//	SetCenter(pos.x, pos.y);
	//}
}

