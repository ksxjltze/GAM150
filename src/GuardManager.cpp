#include "GuardManager.h"
#include "ObjectManager.h"
#include "Sprite.h"
#include "Guard.h"
#include "Detector.h"
#include "Utils.h"

using namespace StarBangBang;

GuardManager::GuardManager(GameObject* gameObject) 
	: Script(gameObject)
{

}

void GuardManager::Init(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client)
{
	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		guards.push_back(objManager->NewGameObject());
		guards[i]->SetPos({ 250, 650 });
		//guards[i]->transform.scale = {0.25f, 0.25f};
		objManager->AddImage(guards[i], *sprite);
		objManager->AddComponent<Guard>(guards[i]);
		objManager->AddComponent<GuardMovement>(guards[i]);
		objManager->AddComponent<GuardVision>(guards[i]).SetPlayerAndClient(player, client);;
		objManager->AddComponent<Detector>(guards[i]);
	}

	guards[0]->SetPos({ 250, 650 });
	//guards[1]->SetPos({ 250, 550 });
}

void GuardManager::Update()
{
	// upon receiving distraction event, get nearest guard to be distracted
	// ...

	if (AEInputCheckTriggered(VK_LBUTTON))
	{
		//guards[0]->GetComponent<GuardMovement>()->SetEndPos(GetMouseWorldPos());
		guards[0]->GetComponent<Guard>()->SetState(Guard::GUARD_STATE::STATE_PATROL);
	}

	if (AEInputCheckTriggered(VK_RBUTTON))
	{
		//guards[1]->GetComponent<GuardMovement>()->LookForPath(GetMouseWorldPos());
		guards[0]->GetComponent<Guard>()->SetState(Guard::GUARD_STATE::STATE_IDLE);
	}
}

GameObject* GuardManager::GetNearestGuard(AEVec2& _pos)
{
	float minDist = AEVec2SquareDistance(&_pos, &guards[0]->transform.position);
	GameObject* nearestGuard = guards[0];

	for (size_t i = 1; i < NUM_GUARDS; i++)
	{
		float dist = AEVec2SquareDistance(&_pos, &guards[i]->transform.position);

		if (dist < minDist)
		{
			minDist = dist;
			nearestGuard = guards[i];
		}
	}

	return nearestGuard;
}