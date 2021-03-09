#pragma once
#include "ScriptComponent.h"
#include "IClickable.h"

namespace StarBangBang
{
	class Click : public Script, public IClickable
	{
	public:
		Click(GameObject* obj);
		void Start();
		void Update();
		virtual void onClick();
	};
}