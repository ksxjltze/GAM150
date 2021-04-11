/******************************************************************************/
/*!
\title		Captain Stealth
\file		ComponentCRTP
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 10, 2021
\brief		Template wrapper around Component class.
			Enables (type) cloning of derived objects through use of the
			Curiously Recurring Template Pattern.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "Component.h"

namespace StarBangBang
{
	template <typename ComponentType>
	class Component : public GameComponent
	{
	public:
		Component(GameObject* obj) : GameComponent(obj) {}
		GameComponent* Clone(GameObject* obj, GameComponent*) const override //const to prevent original component from being modified
		{
			GameComponent* clonedComponent = new ComponentType(static_cast<ComponentType const&>(*this));
			clonedComponent->gameObject = obj;
			return clonedComponent;
		}
	};
}
