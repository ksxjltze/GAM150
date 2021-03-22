#include "SecurityCamera.h"
#include "Detector.h"

using namespace StarBangBang;

SecurityCamera::SecurityCamera(GameObject* gameObject)
	: Script(gameObject)
	, minRot(0.f)
	, maxRot(0.f)
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

	if (!detector)
		detector = gameObject->GetComponent<Detector>();

	detector->Rotate(maxRot);
}

void SecurityCamera::Update()
{
	detector->SpanVision(minRot, maxRot, ROT_SPEED);
	gameObject->transform.rotation = detector->GetRotation();
}