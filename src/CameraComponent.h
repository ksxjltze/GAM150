/******************************************************************************/
/*!
\title		Captain Stealth
\file		CameraComponent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		CameraComponent component class.
			Can be attached to a gameObject to follow it around.
			Supports zooming in and out and can change targets.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ComponentCRTP.h"

namespace StarBangBang
{
	class CameraComponent : public Component<CameraComponent>
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Component Constructor.
		 * Attaches the component to a game object.
		 * \param gameObject
		 * GameObject to attach to.
		***************************************************************************/
		CameraComponent(GameObject* gameObject);

		/*!*************************************************************************
		 * \brief 
		 * LateUpdate function. Called once per frame after Update().
		***************************************************************************/
		void LateUpdate();

		/*!*************************************************************************
		 * \brief 
		 * Sets the Camera Target to follow.
		 * \param obj
		 * GameObject to follow.
		***************************************************************************/
		void SetTarget(GameObject* obj);

		/*!*************************************************************************
		 * \brief 
		 * Enables or disables Camera Zoom.
		 * \param zoom
		 * True to enable camera zoom, false to disable.
		***************************************************************************/
		void EnableZoom(bool zoom);

		/*!*************************************************************************
		 * \brief 
		 * Gets the camera target (GameObject).
		 * \return 
		 * GameObject pointer to the camera target.
		***************************************************************************/
		GameObject* GetTarget();

		AEVec2 position;
		float scale;
		float scaleFactor;
	private:
		bool isZoom{ false };
		GameObject* target;

	};
}