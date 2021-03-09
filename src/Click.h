#pragma once
#include "ScriptComponent.h"
#include "IClickable.h"

namespace StarBangBang
{
	class Click : public Script, public IClickable
	{
	public:
		Click(GameObject* obj, void (*fptr)(void));

		void Start();
		void Update();

		void setCallback(void (*fptr)(void));
		virtual void onClick();
	private:
		void (*callback)(void);
	};
}