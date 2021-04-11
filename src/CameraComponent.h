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
		CameraComponent(GameObject* gameObject);
		void LateUpdate();
		AEVec2 position;
		float scale;
		float scaleFactor;
		void SetTarget(GameObject* obj);
		void EnableZoom(bool zoom);
		GameObject* GetTarget();
	private:
		bool isZoom{ false };
		GameObject* target;

	};
}