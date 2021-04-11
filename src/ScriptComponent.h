/******************************************************************************/
/*!
\title		Captain Stealth
\file		ScriptComponent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		ScriptComponent component class.
			An extension (and abstraction) of the component class.
			Is identical to the component class except that it is
			only to be used for gameplay logic and behavior.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ComponentCRTP.h"

namespace StarBangBang
{
	class Script : public Component<Script>
	{
	public:
		inline Script(GameObject* gameObject) : Component(gameObject) {}
		inline void SetActive(bool status) { active = status; }

		virtual void Start() {};
		virtual void Update() {};
		virtual void Draw() {};

	private:
		friend class ScriptManager;
	};
}