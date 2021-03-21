#include "GuardVision.h"
#include "Guard.h"
#include"GuardMovement.h"
#include "Detector.h"
#include "BasicMeshShape.h"
#include "Utils.h"

using namespace StarBangBang;

GuardVision::GuardVision(GameObject* gameObject)
	: Script(gameObject)
	, detected_player(false)
	, fieldOfView(90.f)
	, viewDist(250.f)
	, player(nullptr)
	, client(nullptr)
	, movement(nullptr)
	, detector(nullptr)
{
}

void GuardVision::Start()
{
	movement = gameObject->GetComponent<GuardMovement>();
	detector = gameObject->GetComponent<Detector>();
	detector->Init(fieldOfView, viewDist, player, client);
}

void GuardVision::Update()
{
	// only update if player or client in same partition grid as guard
	// ...

	AEVec2 defaultForward = { 0, 1 };

	if (movement->IsMoving())
	{
		AEVec2 targetDir, targetPos, goPos;
		AEVec2 defaultLeft = { -1, 0 };
		targetPos = movement->GetNextPos();
		goPos = gameObject->GetPos();

		AEVec2Sub(&targetDir, &targetPos, &goPos);
		AEVec2Normalize(&targetDir, &targetDir);

		float dpResult = AEVec2DotProduct(&defaultForward, &targetDir);
		float rotationAngle = AERadToDeg(AEACos(dpResult));

		float dp = AEVec2DotProduct(&defaultLeft, &targetDir);
		if (dp <= 0.f)
			rotationAngle *= -1;

		detector->SetFacingDir(targetDir);
		detector->Rotate(rotationAngle);
	}
	else
	{
		/*detector->SetFacingDir(defaultForward);
		detector->Rotate(0.f);*/
	}
}