#include "SecurityCamera.h"
#include "Detector.h"
#include "MessageBus.h"
#include "CaughtByCameraEvent.h"

using namespace StarBangBang;

SecurityCamera::SecurityCamera(GameObject* gameObject)
	: Script(gameObject)
	, roomNum(0)
	, minRot(0.f)
	, maxRot(0.f)
	, rotSpeed(GUARD::CAM_ROT_SPEED)
	, detector(nullptr)
	, detected(false)
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
	detector->SpanVision(minRot, maxRot, rotSpeed);
	gameObject->transform.rotation = detector->GetRotation();

	if (detected)
		return;

	AEVec2 targetPos;
	if (detector->GetDetected(targetPos))
	{
		MessageBus::Notify({ EventId::PRINT_TEXT, std::string("DETECTED!") });
		CaughtByCameraEvent e{ gameObject };
		e.pos = targetPos;
		e.roomNum = roomNum;
		e.SendEvent();
		detected = true;
	}
}