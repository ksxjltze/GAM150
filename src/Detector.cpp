#include "Detector.h"
#include "BasicMeshShape.h"
#include "globals.h"

using namespace StarBangBang;

Detector::Detector(GameObject* gameObject)
	: Script(gameObject)
	, fieldOfView(0.f)
	, viewDist(0.f)
	, targetGO(nullptr)
	, rotationAngle(0.f)
	, detected(false)
	, defaultForward({ 0, 1 })
	, targetDir({ 0, 1 })
{
}

void Detector::Init(float fov, float dist, GameObject* target)
{
	fieldOfView = fov;
	viewDist = dist;
	targetGO = target;
}

void Detector::Update()
{
	CheckForTargets();
}

void Detector::Draw()
{
	Color color;

	if (detected)
		color = Red();
	else
		color = White();

	DrawLine(viewDist, gameObject->GetPos(), (fieldOfView * 0.5f) + rotationAngle, color);
	DrawLine(viewDist, gameObject->GetPos(), (-fieldOfView * 0.5f) + rotationAngle, color);
}

void Detector::Rotate(float angle)
{
	rotationAngle = angle;
}

void Detector::CheckForTargets()
{
	// continue only if game objects are in same partition
	// ...
	
	AEVec2 toTargetVec;
	AEVec2 goPos = gameObject->GetPos();
	AEVec2 targetPos = targetGO->GetPos();
	float dpResult;

	// calculate vector from game object to target
	AEVec2Sub(&toTargetVec, &targetPos, &goPos);
	AEVec2Normalize(&toTargetVec, &toTargetVec);

	dpResult = AEVec2DotProduct(&targetDir, &toTargetVec);
	if (dpResult < 0.f) // don't continue if target is behind detector
	{
		detected = false;
		return;
	}

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

			//TEMP
			//gameObject->transform.scale.x += 0.5f * static_cast<float>(g_dt);
			//gameObject->transform.scale.y += 0.5f * static_cast<float>(g_dt);
		}
		else
		{
			detected = false;
			//PRINT("WHERE PLAYER\n");
		}
	}
	else
	{
		detected = false;
		//PRINT("WHERE PLAYER\n");
	}
}