#include "GuardManager.h"
#include "Guard.h"

using namespace StarBangBang;

GuardManager::GuardManager(GameObject* gameObject) 
	: Script(gameObject), objectManager(nullptr), guard_sprite(nullptr)
{

}

void GuardManager::Init()
{
	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		guards.push_back(objectManager->NewGameObject());
		guards[i]->SetPos({ 250, 200 });
		guards[i]->transform.scale = {1.f, 1.f};
		objectManager->AddImage(guards[i], *guard_sprite);
		objectManager->AddComponent<Guard>(guards[i]);
		objectManager->AddComponent<GuardMovement>(guards[i]);
		objectManager->AddComponent<GuardVision>(guards[i]);
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