/******************************************************************************/
/*!
\title		Captain Stealth
\file		CameraComponent.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		CameraComponent component class.
			Can be attached to a gameObject to follow it around.
			Supports zooming in and out and can change targets.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "CameraComponent.h"
#include "GraphicsManager.h"

StarBangBang::CameraComponent::CameraComponent(GameObject* gameObject) : Component<CameraComponent>(gameObject)
{
	position = { 0, 0 };
	scale = GRAPHICS::DEFAULT_ZOOM;
	scaleFactor = GRAPHICS::CAMERA_SCALE_FACTOR;
	target = gameObject;
}

void StarBangBang::CameraComponent::LateUpdate()
{
	float dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	if (isZoom)
	{
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

	}

	//position = gameObject->transform.position;
	position = target->transform.position;
	AEVec2Scale(&position, &position, scale);
	GRAPHICS::SetZoom(scale);

	AEVec2 screenScale = GRAPHICS::GetScreenScale();
	position.x *= screenScale.x;
	position.y *= screenScale.y;


	//temp
	//AEGfxSetCamPosition(position.x, position.y);
	GRAPHICS::SetCameraPosition(position.x, position.y);
}

void StarBangBang::CameraComponent::SetTarget(GameObject* obj)
{
	target = obj;
}

void StarBangBang::CameraComponent::EnableZoom(bool zoom)
{
	isZoom = zoom;
}

StarBangBang::GameObject* StarBangBang::CameraComponent::GetTarget()
{
	return target;
}
