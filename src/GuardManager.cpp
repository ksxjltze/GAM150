#include "GuardManager.h"
#include "ObjectManager.h"
#include "Sprite.h"
#include "Guard.h"
#include "Detector.h"
#include "GuardAnim.h"
#include "SecurityCamera.h"
#include "Physics.h"
#include "DistractionEvent.h"

#include "Utils.h" // for mouseworldpos

#include "Text.h"
#include "globals.h"

using namespace StarBangBang;

GuardManager::GuardManager(GameObject* gameObject) 
	: Script(gameObject)
	, Listener()
{
}

void GuardManager::Init(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client)
{
	int id = 0;

	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		guards.push_back(objManager->NewGameObject());
		//guards[i]->SetPos({ 250, 650 });
		guards[i]->transform.scale = {0.7f, 0.7f};
		guards[i]->name = "Guard";
		objManager->AddImage(guards[i], *sprite);
		objManager->AddComponent<Guard>(guards[i]).SetID(i);
		objManager->AddComponent<GuardMovement>(guards[i]);
		objManager->AddComponent<GuardVision>(guards[i]);
		objManager->AddComponent<Detector>(guards[i]).Init(50.f, 250.f, player, client);
		objManager->AddComponent<Text>(guards[i]).fontID = StarBangBang::fontId;
		objManager->AddComponent<RigidBody>(guards[i]);
		objManager->AddComponent<GuardAnim>(guards[i]);
		objManager->AddCollider(guards[i], false);
	}

	// temp, will change to read from file laterz
	SetGuardWaypoints(id++, { -300, -1085 }, { -420, -1085 });
	SetGuardWaypoints(id++, { -1144, -942}, { -850, -942 });
	SetGuardWaypoints(id++, { -752, -746 }, { -752, -590 });
	SetGuardWaypoints(id++, { -1020, -230 }, { -1020, -670 });
	SetGuardWaypoints(id++, { -740, 100 }, { -740, -80 });
	SetGuardWaypoints(id++, { -180, -50 }, { -20, 120 });
	SetGuardWaypoints(id++, { 350, -240 }, { -195, -240 });
	SetGuardWaypoints(id++, { 455, 190 }, { 630, -415 });
	SetGuardWaypoints(id++, { 160, -1125 }, { 370, -980 });
	SetGuardWaypoints(id++, { 795, -530 }, { 795, -530 }, true); // IDLE
	SetGuardWaypoints(id++, { 930, 830 }, { 0, 515 });
	SetGuardWaypoints(id++, { -195, 790 }, { -815, 540 });
	SetGuardWaypoints(id++, { -1120, 420 }, { -880, 880 });
	SetGuardWaypoints(id++, { 1070, 1011 }, { -733, -1060 }, false, 20.f); // patrol level kinda
	SetGuardWaypoints(id++, { 1055, 145 }, { 1055, -950 }, false, 40.f); // patrol level kinda
}

void GuardManager::CreateSecurityCameras(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client)
{
	int id = 0;

	for (size_t i = 0; i < NUM_CAMERAS; i++)
	{
		cameras.push_back(objManager->NewGameObject());
		cameras[i]->transform.scale = { 0.7f, 0.7f };
		objManager->AddImage(cameras[i], *sprite);
		objManager->AddComponent<SecurityCamera>(cameras[i]);
		objManager->AddComponent<Detector>(cameras[i]).Init(50.f, 300.f, player, client);
	}

	InitSecurityCam(id++, {-1030, -790},	-250.f, -150.f);
	InitSecurityCam(id++, { -250, -520 },	-270.f, -130.f);
	InitSecurityCam(id++, { -620, 190 },	-200.f,  -80.f,		60.f);
	InitSecurityCam(id++, { 470, -480 },	   0.f,   90.f);
	InitSecurityCam(id++, { -645, -410 },	 -90.f,    0.f,		60.f);
	InitSecurityCam(id++, { 1020, 350 },	   0.f,   90.f,		60.f);
	InitSecurityCam(id++, { -180, 340 },	   0.f,   90.f);
	InitSecurityCam(id++, { -13, 1165 },	-180.f,  -90.f);
	InitSecurityCam(id++, { -1160, 1130 },	-180.f,  -90.f,		60.f);
	InitSecurityCam(id++, { -690, 720 },	   0.f,  360.f);
}

void GuardManager::Update()
{
	//PRINT("x: %f, y: %f\n", GetMouseWorldPos().x, GetMouseWorldPos().y);

	// upon receiving distraction event, get nearest guard to be distracted
	// ...

	if (AEInputCheckTriggered(VK_LBUTTON))
	{
		//guards[0]->GetComponent<GuardMovement>()->SetEndPos(GetMouseWorldPos());
		//guards[0]->GetComponent<Guard>()->ChangeState(Guard::GUARD_STATE::STATE_PATROL);
	}

	if (AEInputCheckTriggered(VK_RBUTTON))
	{
		//guards[1]->GetComponent<GuardMovement>()->LookForPath(GetMouseWorldPos());
		//guards[0]->GetComponent<Guard>()->ChangeState(Guard::GUARD_STATE::STATE_IDLE);
	}
}

void GuardManager::onNotify(Event e)
{
	if (e.id == EventId::DISTRACTION)
	{
		DistractionEvent distraction = std::any_cast<DistractionEvent>(e.context);
		AEVec2 distractPos = distraction.gameObject->GetPos();
		GameObject* guard = GetNearestGuard(distractPos);

		if (!guard)
		{
			//std::cout << "No guard nearby\n";
			return;
		}

		std::cout << "GUARD DISTRACTED! GUARD ID: " << guard->GetComponent<Guard>()->GetID() << std::endl;
		guard->GetComponent<GuardMovement>()->SetTargetPos(distractPos);
		guard->GetComponent<Guard>()->ChangeState(Guard::GUARD_STATE::STATE_DISTRACTED);
	}
}

GameObject* GuardManager::GetNearestGuard(const AEVec2& _pos)
{
	AEVec2 distractionPos = _pos;
	float minDist = 999999.f;
	GameObject* nearestGuard = nullptr;
	
	//AEVec2SquareDistance(&distractionPos, &guards[0]->transform.position);
	//GameObject* nearestGuard = guards[0];

	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		// only look for guards not currently distracted
		if (guards[i]->GetComponent<Guard>()->GetState() == Guard::GUARD_STATE::STATE_DISTRACTED)
			continue;

		float dist = AEVec2SquareDistance(&distractionPos, &guards[i]->transform.position);

		if (dist < minDist)
		{
			minDist = dist;
			nearestGuard = guards[i];
		}
	}

	return nearestGuard;
}

void GuardManager::SetGuardWaypoints(int id, const AEVec2& start, const AEVec2& end, bool isIdle, float speed)
{
	guards[id]->GetComponent<GuardMovement>()->SetStartEndPos(start, end, isIdle);

	if (isIdle)
	{
		guards[id]->GetComponent<Guard>()->ChangeState(Guard::GUARD_STATE::STATE_IDLE);
	}

	guards[id]->GetComponent<GuardMovement>()->SetSpeed(speed);
}

void GuardManager::InitSecurityCam(int id, const AEVec2& pos, float min, float max, float speed)
{
	cameras[id]->SetPos(pos);
	cameras[id]->GetComponent<SecurityCamera>()->SetRotationMinMax(min, max);
	cameras[id]->GetComponent<SecurityCamera>()->SetRotSpeed(speed);
}