#include "GuardVision.h"
#include "Guard.h"
#include"GuardMovement.h"
#include "Detector.h"
#include "BasicMeshShape.h"
#include "Utils.h"
#include "globals.h"

using namespace StarBangBang;

GuardVision::GuardVision(GameObject* gameObject)
	: Script(gameObject)
	, movement(nullptr)
	, detector(nullptr)
	, rotation(0.f)
	, prevRot(-1)
	, currRot(0)
	, turn(false)
{
}

void GuardVision::Start()
{
	movement = gameObject->GetComponent<GuardMovement>();
	detector = gameObject->GetComponent<Detector>();
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
		float targetRot = AERadToDeg(AEACos(dpResult));

		float dp = AEVec2DotProduct(&defaultLeft, &targetDir);
		if (dp < 0.f)
			targetRot = -targetRot;

		detector->SetFacingDir(targetDir);
		detector->Rotate(targetRot);

		//currRot = static_cast<int>(rint(targetRot));

		//if (currRot != prevRot)
		//{
		//	prevRot = currRot;
		//	turn = true;
		//	movement->SetTurning(true);
		//	PRINT("target rot: %d\n", currRot);
		//}

		//if (turn)
		//{
		//	// eg. prevRot = -180, currRot = 90;
		//	// i want it to change to 90 from -180

		//	// 1. i can either make -180 a positive
		//	// 2. or 


		//	if (currRot >= 0)
		//	{
		//		if (rotation <= targetRot)
		//		{
		//			rotation += 50.f * g_dt;
		//			PRINT("increasing\n");
		//			FaceTowardsRotation();
		//		}
		//		else
		//		{
		//			movement->SetTurning(false);
		//			turn = false;
		//			detector->SetFacingDir(targetDir);
		//		}
		//	}
		//	else
		//	{
		//		if (rotation >= targetRot)
		//		{
		//			PRINT("decreasing\n");
		//			rotation -= 50.f * g_dt;
		//			FaceTowardsRotation();
		//		}
		//		else
		//		{
		//			movement->SetTurning(false);
		//			turn = false;
		//			detector->SetFacingDir(targetDir);
		//		}
		//	}
		//	
		//	detector->Rotate(targetRot);
		//}
	}
	else
	{
		/*detector->SetFacingDir(defaultForward);
		detector->Rotate(0.f);*/
	}
}

void GuardVision::FaceTowardsRotation()
{
	AEVec2 facingDir;
	AEVec2FromAngle(&facingDir, AEDegToRad(90.f + rotation));
	detector->SetFacingDir(facingDir);
}