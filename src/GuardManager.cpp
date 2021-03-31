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
	SetGuardStartEnd(id++, { -322, -1163 }, { -322, -596 });
	SetGuardStartEnd(id++, { -72, -1162}, { -72, -385 });
	SetGuardStartEnd(id++, { -42, -1203 }, { 1069, -1203 });
	SetGuardStartEnd(id++, { 900, -1009 }, { 906, -456 });
	//SetGuardWaypoints(id++, { -740, 100 }, { -740, -80 }); CIRCLE GUARD
	SetGuardStartEnd(id++, { 945, -93 }, { 198, -93 });
	SetGuardStartEnd(id++, { -225, -42 }, { -225, 296 });
	SetGuardStartEnd(id++, { -251, 958 }, { -251, 605 });
	SetGuardStartEnd(id++, { -13, 889 }, { 754, 895 });
	//SetGuardWaypoints(id++, { 795, -530 }, { 795, -530 }, true); // IDLE
	SetGuardStartEnd(id++, { 330, 282 }, { 893, 282 });
	//SetGuardWaypoints(id++, { -195, 790 }, { -815, 540 }); complex guard
	SetGuardStartEnd(id++, { 1118, 68 }, { 1118, 671 });
	//SetGuardWaypoints(id++, { 44, -873 }, { 330, -873 });
	SetGuardStartEnd(id++, { 466, -589 }, { 769, -589 });
	SetGuardStartEnd(id++, { 751, -835 }, { 491, -853 });
	SetGuardStartEnd(id++, { 314, -461 }, { 314, -954 });
	SetGuardStartEnd(id++, { 783, 551 }, { 428, 551 });
	//last
	SetGuardStartEnd(id++, { -667, 1015 }, { -911, 1015 });
	SetGuardStartEnd(id++, { -849, 806 }, { -849, 949 });
	SetGuardStartEnd(id++, { -1022, 651 }, { -715, 651 });
	SetGuardStartEnd(id++, { -821, 544 }, { -821, 358 });
	SetGuardStartEnd(id++, { -489, 972 }, { -489, 635 });
	SetGuardStartEnd(id++, { -469, 382 }, { -469, 100 });
	SetGuardStartEnd(id++, { -617, 175 }, { -617, 459 });
	SetGuardStartEnd(id++, { -817, 47 }, { -1024, 47 });
	SetGuardStartEnd(id++, { -757, -250 }, { -1003, -250 });

	//SetGuardWaypoints(id++, { 1070, 1011 }, { -733, -1060 }, false, 20.f); // patrol level kinda
	//SetGuardWaypoints(id++, { 1055, 145 }, { 1055, -950 }, false, 40.f); // patrol level kinda
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

	InitSecurityCam(id++, {1157, -1205},	-250.f, -150.f);
	//InitSecurityCam(id++, { -250, -520 },	-270.f, -130.f);
	//InitSecurityCam(id++, { -620, 190 },	-200.f,  -80.f,		60.f);
	//InitSecurityCam(id++, { 470, -480 },	   0.f,   90.f);
	//InitSecurityCam(id++, { -645, -410 },	 -90.f,    0.f,		60.f);
	//InitSecurityCam(id++, { 1020, 350 },	   0.f,   90.f,		60.f);
	//InitSecurityCam(id++, { -180, 340 },	   0.f,   90.f);
	//InitSecurityCam(id++, { -13, 1165 },	-180.f,  -90.f);
	//InitSecurityCam(id++, { -1160, 1130 },	-180.f,  -90.f,		60.f);
	//InitSecurityCam(id++, { -690, 720 },	   0.f,  360.f);
}

void GuardManager::Update()
{
	PRINT("x: %f, y: %f\n", GetMouseWorldPos().x, GetMouseWorldPos().y);

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

void GuardManager::SetGuardStartEnd(int id, const AEVec2& start, const AEVec2& end, bool isIdle, float speed)
{
	guards[id]->GetComponent<GuardMovement>()->SetSpeed(speed);
	guards[id]->GetComponent<GuardMovement>()->SetStartEndPos(start, end, isIdle);

	if (isIdle)
	{
		guards[id]->GetComponent<Guard>()->ChangeState(Guard::GUARD_STATE::STATE_IDLE);
	}
}

void GuardManager::SetGuardWaypoints(int id, std::vector<AEVec2>& waypoints, float speed)
{
	guards[id]->GetComponent<GuardMovement>()->SetSpeed(speed);
	guards[id]->GetComponent<GuardMovement>()->SetWaypoints(waypoints);
	guards[id]->SetPos(waypoints.front());
}

void GuardManager::InitSecurityCam(int id, const AEVec2& pos, float min, float max, float speed)
{
	cameras[id]->SetPos(pos);
	cameras[id]->GetComponent<SecurityCamera>()->SetRotationMinMax(min, max);
	cameras[id]->GetComponent<SecurityCamera>()->SetRotSpeed(speed);
}