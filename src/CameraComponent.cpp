#include "CameraComponent.h"
#include "GraphicsManager.h"

StarBangBang::CameraComponent::CameraComponent(GameObject* gameObject) : Component<CameraComponent>(gameObject)
{
	position = { 0, 0 };
	scale = 1.0f;
	scaleFactor = GRAPHICS::CAMERA_SCALE_FACTOR;
}

void StarBangBang::CameraComponent::LateUpdate()
{
	float dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	if (AEInputCheckCurr(AEVK_MINUS))
	{
		scale -= scaleFactor * dt;
		if (scale < GRAPHICS::CAMERA_SCALE_MIN)
			scale = GRAPHICS::CAMERA_SCALE_MIN;
	}
	else if (AEInputCheckCurr(AEVK_EQUAL))
	{
		scale += scaleFactor * dt;
		if (scale > GRAPHICS::CAMERA_SCALE_MAX)
			scale = GRAPHICS::CAMERA_SCALE_MAX;
	}

	position = gameObject->transform.position;
	AEVec2Scale(&position, &position, scale);
	GRAPHICS::SetZoom(scale);


	//temp
	AEGfxSetCamPosition(position.x, position.y);
}
