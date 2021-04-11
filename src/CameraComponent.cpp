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

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#include "CameraComponent.h"
#include "GraphicsManager.h"

/*!*************************************************************************
	* \brief
	* Component Constructor.
	* Attaches the component to a game object.
	* \param gameObject
	* GameObject to attach to.
***************************************************************************/
StarBangBang::CameraComponent::CameraComponent(GameObject* gameObject) : Component<CameraComponent>(gameObject)
{
	position = { 0, 0 };
	scale = GRAPHICS::DEFAULT_ZOOM;
	scaleFactor = GRAPHICS::CAMERA_SCALE_FACTOR;
	target = gameObject;
}

/*!*************************************************************************
 * \brief
 * LateUpdate function. Called once per frame after Update().
***************************************************************************/
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

/*!*************************************************************************
 * \brief
 * Sets the Camera Target to follow.
 * \param obj
 * GameObject to follow.
***************************************************************************/
void StarBangBang::CameraComponent::SetTarget(GameObject* obj)
{
	target = obj;
}

/*!*************************************************************************
 * \brief
 * Enables or disables Camera Zoom.
 * \param zoom
 * True to enable camera zoom, false to disable.
***************************************************************************/
void StarBangBang::CameraComponent::EnableZoom(bool zoom)
{
	isZoom = zoom;
}

/*!*************************************************************************
 * \brief
 * Gets the camera target (GameObject).
 * \return
 * GameObject pointer to the camera target.
***************************************************************************/
StarBangBang::GameObject* StarBangBang::CameraComponent::GetTarget()
{
	return target;
}
