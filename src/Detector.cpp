#include "Detector.h"
#include "BasicMeshShape.h"
#include "globals.h"
#include "MessageBus.h"
#include "CollisionManager.h"

using namespace StarBangBang;

Detector::Detector(GameObject* gameObject)
	: Script(gameObject)
	, fieldOfView(0.f)
	, viewDist(0.f)
	, target1(nullptr)
	, target2(nullptr)
	, target1Col(nullptr)
	, target2Col(nullptr)
	, myCollider(nullptr)
	, rotationAngle(0.f)
	, atMaxRot(false)
	, detectedTarget1(false)
	, detectedTarget2(false)
	, defaultForward({ 0, 1 })
	, targetDir({ 0, 1 })
{
}

void Detector::Init(float fov, float dist, GameObject* player, GameObject* client)
{
	fieldOfView = fov;
	viewDist = dist;
	target1 = player;
	target2 = client;
	target1Col = target1->GetComponent<BoxCollider>();
	target2Col = target2->GetComponent<BoxCollider>();
	myCollider = gameObject->GetComponent<BoxCollider>();
}

void Detector::Update()
{
	if (target1->active)
		CheckForTargets(target1->GetPos());
	if (target2->active)
		CheckForTargets(target2->GetPos(), false);
}

void Detector::Draw()
{
	Color color;

	if (detectedTarget1 || detectedTarget2)
		color = Red;
	else if (!detectedTarget1 && !detectedTarget2)
		color = White;

	DrawLine(viewDist, gameObject->GetPos(), (fieldOfView * 0.5f) + rotationAngle, color);
	DrawLine(viewDist, gameObject->GetPos(), (-fieldOfView * 0.5f) + rotationAngle, color);
	//DrawLine(viewDist, gameObject->GetPos(), rotationAngle, color);
}

void Detector::Rotate(float angle)
{
	rotationAngle = angle;
}

void Detector::SpanVision(float minRot, float maxRot, float speed)
{
	if (!atMaxRot && rotationAngle <= maxRot)
	{
		rotationAngle += static_cast<float>(g_dt) * speed;
	}
	else
	{
		atMaxRot = true;
	}

	if (atMaxRot && rotationAngle >= minRot)
	{
		rotationAngle -= static_cast<float>(g_dt) * speed;
	}
	else
	{
		atMaxRot = false;
	}

	AEVec2 facingDir;
	AEVec2FromAngle(&facingDir, AEDegToRad(90.f + rotationAngle));
	targetDir = facingDir;
}

void Detector::CheckForTargets(const AEVec2& _targetPos, bool checkForPlayer)
{
	// continue only if game objects are in same partition
	// ...

	BoxCollider* collider = nullptr;

	if (checkForPlayer)
		collider = target1Col;
	else
		collider = target2Col;
	
	AEVec2 toTargetVec;
	AEVec2 goPos = gameObject->GetPos();
	AEVec2 targetPos = _targetPos;

	// calculate vector from game object to target
	AEVec2Sub(&toTargetVec, &targetPos, &goPos);
	AEVec2Normalize(&toTargetVec, &toTargetVec);

	float dpResult = AEVec2DotProduct(&targetDir, &toTargetVec);
	if (dpResult < 0.f) // don't continue if target is behind detector
	{
		if (checkForPlayer)
			detectedTarget1 = false;
		else
			detectedTarget2 = false;

		return;
	}

	float angle = AEACos(dpResult);
	angle = AERadToDeg(angle);

	if (AEVec2SquareDistance(&targetPos, &goPos) <= viewDist * viewDist)
	{
		if (angle < (fieldOfView * 0.5f))
		{
			// check if vision is colliding with environment first
			Ray ray = Ray(gameObject->GetPos(), _targetPos);

			if (CollisionManager::LineCast(ray, myCollider) == collider)
			{
				SetDetected(checkForPlayer, true);

				//Event test
				if (detectedTarget1)
					MessageBus::Notify({ EventId::DETECTED, target1 });
				else if (detectedTarget2)
					MessageBus::Notify({ EventId::DETECTED, target2 });
			}
			else
			{
				SetDetected(checkForPlayer, false);
			}
		}
		else
		{
			SetDetected(checkForPlayer, false);
		}
	}
	else
	{
		SetDetected(checkForPlayer, false);
	}
}

void Detector::SetDetected(bool checkForPlayer, bool detected)
{
	if (checkForPlayer)
		detectedTarget1 = detected;
	else
		detectedTarget2 = detected;
}