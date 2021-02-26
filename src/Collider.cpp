#include "Collider.h"
#include "CollisionManager.h"

using namespace StarBangBang;

void BoxCollider::SetCenter(float x, float y)
{
	center.x = x;
	center.y = y;
}
void BoxCollider::Translate(float x , float y)
{
	center.x += x;
	center.y += y;
}

void BoxCollider::ClearCellList()
{
	cell_indexes.clear();
}

void BoxCollider::AddToCellList(unsigned int x , unsigned int y)
{
	cell_indexes.push_back(CellIndexes{x,y});
}

const std::vector<CellIndexes>& BoxCollider::GetCellIndexes() const
{
	return cell_indexes;
}


BoxCollider::BoxCollider(AEVec2 _center, bool _isStatic , float width, float height) : Collider()
{
	extend = AEVec2{ width * 0.5f,height * 0.5f};
	min = AEVec2{_center.x - extend.x , _center.y - extend.y} ;
	max = AEVec2{ _center.x + extend.x , _center.y + extend.y };
	isStatic = _isStatic;
	center = _center;
	CollisionManager::AddToColliders(*this);
	
}
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
