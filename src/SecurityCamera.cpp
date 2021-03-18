#include "SecurityCamera.h"
#include "Detector.h"
#include "globals.h"

using namespace StarBangBang;

SecurityCamera::SecurityCamera(GameObject* gameObject)
	: Script(gameObject)
	, atMaxRot(false)
	, minRot(0.f)
	, maxRot(0.f)
	, rotation(0.f)
	, detector(nullptr)
{

}

void SecurityCamera::Start()
{
	detector = gameObject->GetComponent<Detector>();
}

void SecurityCamera::SetRotationMinMax(float _minRot, float _maxRot)
{
	minRot = _minRot;
	maxRot = _maxRot;
	rotation = minRot;
}

void SecurityCamera::Update()
{
	if (!atMaxRot && rotation <= maxRot)
	{
		rotation += static_cast<float>(g_dt) * ROT_SPEED;
	}
	else
	{
		atMaxRot = true;
	}

	if (atMaxRot && rotation >= minRot)
	{
		rotation -= static_cast<float>(g_dt) * ROT_SPEED;
	}
	else
	{
		atMaxRot = false;
	}

	// need to rotate targetDir
	detector->Rotate(rotation);

	AEVec2 facingDir;
	AEVec2FromAngle(&facingDir, AEDegToRad(90.f + rotation));
	detector->SetFacingDir(facingDir);
}