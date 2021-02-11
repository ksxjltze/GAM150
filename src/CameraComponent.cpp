#include "CameraComponent.h"
#include "GraphicsManager.h"

StarBangBang::CameraComponent::CameraComponent(GameObject* gameObject) : Component<CameraComponent>(gameObject)
{
	position = { 0, 0 };
	scale = 1.0f;
	scaleFactor = 0.5f;
}

void StarBangBang::CameraComponent::Update()
{
	float dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	if (AEInputCheckCurr(AEVK_MINUS))
	{
		scale -= scaleFactor * dt;
	}
	else if (AEInputCheckCurr(AEVK_EQUAL))
	{
		scale += scaleFactor * dt;
	}

	position = gameObject->transform.position;
	Graphics::SetZoom(scale);


	//temp
	AEGfxSetCamPosition(position.x, position.y);
}
