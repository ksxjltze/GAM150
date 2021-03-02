#include "Collider.h"
#include "CollisionManager.h"

using namespace StarBangBang;



void BoxCollider::SetCenter(float x, float y)
{
	center.x = x;
	center.y = y;
	//CollisionManager::RecalculateColliderCells(this);
}
void BoxCollider::Translate(float x , float y)
{
	center.x += x;
	center.y += y;
	//CollisionManager::RecalculateColliderCells(this);
}

void BoxCollider::ClearCellList()
{
	cell_indexes.clear();
}

unsigned int StarBangBang::BoxCollider::GetCellListSize() const
{
	return (unsigned int)cell_indexes.size();
}

void BoxCollider::AddToCellList(unsigned int x , unsigned int y)
{
	for (const CellIndexes& c : cell_indexes)
	{
		if (c.x == x && c.y == y)
			return;
	}
	cell_indexes.push_back(CellIndexes{ x,y });
	
}

const std::vector<CellIndexes>& BoxCollider::GetCellIndexes() const
{
	return cell_indexes;
}
BoxCollider::BoxCollider(AEVec2 min, AEVec2 max,bool isStatic) 
{
	this->min = min;
	this->max = max;
	this->isStatic = isStatic;
	float width = max.x - min.x;
	float height = max.y - min.y;
	extend = AEVec2{ width * 0.5f,height * 0.5f };
	center = AEVec2{min.x + extend.x, min.y + extend.y};
	CollisionManager::AddToColliders(*this);
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
BoxCollider BoxCollider::Union(const BoxCollider& b1)
{

	AEVec2 newMin, newMax;
	newMin.x = min(Min().x, b1.Min().x);
	newMin.y = min(Min().y, b1.Min().y);
	newMax.x = max(Max().x, b1.Max().x);
	newMax.y = max(Max().y, b1.Max().y);

	return BoxCollider(newMin,newMax);
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
