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
	, rotSpeed(90.f)
	, idleDuration(1.5f)
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

	if (gameObject->GetComponent<Guard>()->GetState() == Guard::GUARD_STATE::STATE_CHASE)
	{
		rotSpeed = 350.f;
	}

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

		if (gameObject->GetComponent<Guard>()->GetState() == Guard::GUARD_STATE::STATE_PATROL)
		{
			float dp = AEVec2DotProduct(&defaultLeft, &targetDir);
			if (dp < 0.f)
				targetRot = -targetRot;
		}

		currRot = static_cast<int>(rint(targetRot));

		if (currRot != prevRot)
		{
			//PRINT("TURNING, %d\n", (prevRot - currRot));
			/*if (currRot == 0)
				currRot = 1;*/

			if (targetRot > 0 && rotation < 0.f)
			{
				if ((static_cast<int>(rotation) + static_cast<int>(targetRot)) != 0)
					targetRot = -targetRot; //rotation = -rotation;
			}
			else if (targetRot < 0 && rotation > 0.f)
			{
				if ((static_cast<int>(rotation) + static_cast<int>(targetRot)) != 0)
					targetRot = -targetRot; //rotation = -rotation;
			}

			prevRot = currRot;
			turn = true;
			movement->SetTurning(true);
			//PRINT("target rot: %f, rotation: %f\n", targetRot, rotation);
		}

		if (turn)
		{
			idleDuration -= g_dt;
			if (idleDuration > 0.f)
				return;

			if (rotation + 3.f < targetRot)
			{
				rotation += rotSpeed * g_dt;
				FaceTowardsRotation();
			}
			else if (rotation - 3.f > targetRot)
			{
				rotation -= rotSpeed * g_dt;
				FaceTowardsRotation();
			}
			
			if ((rotation - targetRot) >= -3.f && (rotation - targetRot) <= 3.f)
			{
				movement->SetTurning(false);
				turn = false;
				rotation = targetRot;
				idleDuration = 1.5f;
				detector->SetFacingDir(targetDir);
			}
			
			detector->Rotate(rotation);
		}
	}
	else
	{
		/*detector->SetFacingDir(defaultForward);
		detector->Rotate(0.f);*/
	}
}

void GuardVision::Idle()
{
	if (gameObject->GetComponent<Guard>()->GetPrevState() == Guard::GUARD_STATE::STATE_DISTRACTED)
	{
		AEVec2 defaultForward = { 0, 1 };
		AEVec2 targetDir, targetPos, goPos;
		AEVec2 defaultLeft = { -1, 0 };
		targetPos = movement->GetTargetPos(); // look at distraction object
		goPos = gameObject->GetPos();

		AEVec2Sub(&targetDir, &targetPos, &goPos);
		AEVec2Normalize(&targetDir, &targetDir);

		float dpResult = AEVec2DotProduct(&defaultForward, &targetDir);
		float targetRot = AERadToDeg(AEACos(dpResult));

		float dp = AEVec2DotProduct(&defaultLeft, &targetDir);
		if (dp < 0.f)
			targetRot = -targetRot;

		detector->SpanVision(targetRot - 90.f, targetRot + 90.f, 50.f);
	}
}

void GuardVision::FaceTowardsRotation()
{
	AEVec2 facingDir;
	AEVec2FromAngle(&facingDir, AEDegToRad(90.f + rotation));
	detector->SetFacingDir(facingDir);
}