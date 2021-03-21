#include "GuardManager.h"
#include "ObjectManager.h"
#include "Sprite.h"
#include "Guard.h"
#include "Detector.h"
#include "SecurityCamera.h"
#include "Physics.h"

#include "Utils.h" // for mouseworldpos

#include "Text.h"
#include "globals.h"

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
		//guards[i]->SetPos({ 250, 650 });
		guards[i]->transform.scale = {0.5f, 0.5f};
		objManager->AddImage(guards[i], *sprite);
		objManager->AddComponent<Guard>(guards[i]);
		objManager->AddComponent<GuardMovement>(guards[i]);
		objManager->AddComponent<GuardVision>(guards[i]).SetPlayerAndClient(player, client);
		objManager->AddComponent<Detector>(guards[i]);
		objManager->AddComponent<Text>(guards[i]).fontID = StarBangBang::fontId;
		objManager->AddComponent<RigidBody>(guards[i]);
	}

	// temp, will change to read from file laterz
	SetGuardWaypoints({ -300, -1085 }, { -420, -1085 });
	SetGuardWaypoints({ -1144, -942}, { -850, -942 });
	SetGuardWaypoints({ -752, -746 }, { -752, -590 });
	SetGuardWaypoints({ -1020, -230 }, { -1020, -670 });
	SetGuardWaypoints({ -750, 100 }, { -750, -90 });
	SetGuardWaypoints({ -180, -50 }, { -20, 120 });
	SetGuardWaypoints({ 350, -250 }, { -195, -250 });
	SetGuardWaypoints({ 455, 190 }, { 630, -415 });
	SetGuardWaypoints({ 160, -1125 }, { 370, -980 });
	SetGuardWaypoints({ 795, -530 }, { 795, -530 }, true); // IDLE
	SetGuardWaypoints({ 930, 830 }, { 0, 515 });
	SetGuardWaypoints({ -195, 790 }, { -815, 540 });
	SetGuardWaypoints({ -1120, 420 }, { -880, 880 });
}

void GuardManager::CreateSecurityCameras(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client)
{
	for (size_t i = 0; i < 1; i++)
	{
		cameras.push_back(objManager->NewGameObject());
		//cameras[i]->transform.scale = { 0.5f, 0.5f };
		objManager->AddImage(cameras[i], *sprite);
		objManager->AddComponent<SecurityCamera>(cameras[i]).SetRotationMinMax(-90.f, 90.f);
		objManager->AddComponent<Detector>(cameras[i]);
		cameras[i]->GetComponent<Detector>()->Init(90.f, 250.f, player, client);
		cameras[i]->SetPos({ 100, 750 });
	}
}

void GuardManager::Update()
{
	PRINT("x: %f, y: %f\n", GetMouseWorldPos().x, GetMouseWorldPos().y);

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

void GuardManager::SetGuardWaypoints(const AEVec2& start, const AEVec2& end, bool isIdle)
{
	static int id = 0;
	guards[id]->GetComponent<GuardMovement>()->SetStartEndPos(start, end);

	if (isIdle)
		guards[id]->GetComponent<Guard>()->SetState(Guard::GUARD_STATE::STATE_IDLE);

	++id;
}