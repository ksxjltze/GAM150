#pragma once
#include "ScriptComponent.h"
#include "ImageComponent.h"
#include "UIComponent.h"
#include "Text.h"

namespace StarBangBang
{
	
	class StealthWalk : public Script
	{
	public:
		StealthWalk(GameObject* gameObject);
		void Start();
		void Update();
		bool IsInvisible() { return invisible; }
		float GetTimer() { return timer; }
		float GetCooldown() { return cooldown; }
	private:
		ImageComponent* image;
		UIComponent* icon_image;
		Text* cd_txt;
		float timer;
		float cooldown;
		bool invisible = false;
		
	};
}