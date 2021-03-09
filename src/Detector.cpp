#include "Detector.h"
#include "BasicMeshShape.h"

using namespace StarBangBang;

Detector::Detector(GameObject* gameObject)
	: Script(gameObject)
	, fieldOfView(0.f)
	, viewDist(0.f)
	, targetGO(nullptr)
	, rotationAngle(0.f)
	, detected(false)
	, isFixedPos(false)
	, defaultForward({ 0, 1 })
	, targetDir({ 0, 1 })
{
}

void Detector::Init(float fov, float dist, bool fixedPos, GameObject* target)
{
	fieldOfView = fov;
	viewDist = dist;
	isFixedPos = fixedPos;
	targetGO = target;
}

void Detector::Update()
{
	if (isFixedPos) // this detector is a security cam
	{
		// security cam behaviour (TEMP)
		rotationAngle += AEFrameRateControllerGetFrameTime() * 50.f;
		if (rotationAngle > 360.f)
			rotationAngle = 0.f;
		
		// need to rotate targetDir
		Rotate(rotationAngle);
	}

	CheckForTargets();
	DrawVision(gameObject->GetPos());
}

void Detector::Rotate(float angle)
{
	rotationAngle = angle;

	if (isFixedPos)
	{
		AEVec2FromAngle(&targetDir, AEDegToRad(90.f + rotationAngle));
	}
}

void Detector::DrawVision(const AEVec2& pos)
{
	DrawLine(viewDist + 50.f, pos, (fieldOfView * 0.5f) + rotationAngle);
	DrawLine(viewDist + 50.f, pos, (-fieldOfView * 0.5f) + rotationAngle);
}

void Detector::CheckForTargets()
{
	AEVec2 toTargetVec;
	AEVec2 goPos = gameObject->GetPos();
	AEVec2 targetPos = targetGO->GetPos();
	float dpResult;

	// calculate vector from game object to target
	AEVec2Sub(&toTargetVec, &targetPos, &goPos);
	AEVec2Normalize(&toTargetVec, &toTargetVec);

	dpResult = AEVec2DotProduct(&targetDir, &toTargetVec);
	//if (dpResult < 0.f) // don't continue if target is behind detector
		//return;

	float angle = AEACos(dpResult);
	angle = AERadToDeg(angle);

	if (AEVec2SquareDistance(&targetPos, &goPos) <= viewDist * viewDist)
	{
		if (angle < (fieldOfView * 0.5f))
		{
			// check if vision is colliding with environment first
			// ...

			//PRINT("%s\n", "DETECTED PLAYER");
			detected = true;
		}
		//else
			//PRINT("WHERE PLAYER\n");
	}
	//else
		//PRINT("WHERE PLAYER\n");
}