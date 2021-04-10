/******************************************************************************/
/*!
\title		Captain Stealth
\file		Component.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Component class. Is responsible for driving game behavior.
			Must be attached to a game object.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "GameObject.h"
#include "constants.h"

namespace StarBangBang
{
	class ObjectManager;

	class GameComponent
	{
	public:
		GameComponent(GameObject* gameObject) { this->gameObject = gameObject; }
		virtual GameComponent* Clone(GameObject* obj, GameComponent*) const { return new GameComponent(obj); }
		virtual void Start() {};
		virtual void Update() {};
		virtual void Draw() {};
		virtual void LateUpdate() {};
		GameObject* gameObject { nullptr };
		virtual ~GameComponent() {}
		bool drawable{ false };
		bool active { true };
		ObjectManager* objMgr{ nullptr };

	};
}