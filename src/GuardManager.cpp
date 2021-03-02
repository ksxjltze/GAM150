#include "GuardManager.h"
#include "ObjectManager.h"
#include "Guard.h"

using namespace StarBangBang;

GuardManager::GuardManager(GameObject* gameObject) 
	: Script(gameObject)
{

}

void GuardManager::Init(ObjectManager* objManager, Sprite* sprite)
{
	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		guards.push_back(objManager->NewGameObject());
		guards[i]->SetPos({ 250, 700 });
		guards[i]->transform.scale = {0.25f, 0.25f};
		objManager->AddImage(guards[i], *sprite);
		objManager->AddComponent<Guard>(guards[i]);
		objManager->AddComponent<GuardMovement>(guards[i]);
		objManager->AddComponent<GuardVision>(guards[i]);
	}
}

void GuardManager::Update()
{
	// upon receiving distraction event, get nearest guard to be distracted
	// ...
}

GameObject* GuardManager::GetNearestGuard(AEVec2& _pos)
{
	float min_dist = 0.f;
	GameObject* nearestGuard = nullptr;

	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		float dist = AEVec2SquareDistance(&_pos, &guards[i]->transform.position);

		if (min_dist == 0.f || dist < min_dist)
		{
			min_dist = dist;
			nearestGuard = guards[i];
		}
	}

	return nearestGuard;
}