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

unsigned int StarBangBang::BoxCollider::GetCellListSize() const
{
	return (unsigned int)cell_indexes.size();
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

	center = _center;
	CollisionManager::AddToColliders(*this);
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

void StarBangBang::BoxCollider::Update()
{
	if (gameObject)
	{
		//printf("%f, %f\n", gameObject->transform.position.x, gameObject->transform.position.y);
		//printf("%f, %f\n", center.x, center.y);

		float dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
		float speed = PLAYER::PLAYER_SPEED * dt;
		if (AEInputCheckCurr(AEVK_W))
		{
			Translate(0, speed);
		}
		if (AEInputCheckCurr(AEVK_A))
		{
			Translate(-speed, 0);
		}
		if (AEInputCheckCurr(AEVK_S))
		{
			Translate(0, -speed);
		}
		if (AEInputCheckCurr(AEVK_D))
		{
			Translate(speed, 0);
		}

		gameObject->SetPos({ center.x, center.y });
	}
}

void StarBangBang::CircleCollider::Update()
{
	//if (gameObject)
	//{
	//	AEVec2 pos = gameObject->GetPos();
	//	SetCenter(pos.x, pos.y);
	//}
}

