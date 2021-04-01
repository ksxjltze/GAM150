#pragma once
#include "ScriptComponent.h"
#include "IClickable.h"
#include "Utils.h"
#include "SoundEvent.h"

namespace StarBangBang
{
	template <typename ClassType>
	class Click : public Script, public IClickable
	{
	public:
		Click(GameObject* obj, bool overlay = false) : Script(obj), isOverlay{ overlay } {}
		Click(GameObject* obj, void (*fptr)(void)) : Script(obj), callback{ fptr } {}

		void Start() {  }
		void Update()
		{
			if (AEInputCheckTriggered(AEVK_LBUTTON))
			{
				Transform& transform = gameObject->transform;
				if (PointRectTest(GetMouseWorldPos(!isOverlay), transform.position, transform.scale.x * GRAPHICS::MESH_WIDTH, transform.scale.y * GRAPHICS::MESH_HEIGHT))
				{
					onClick();
				}
		
			}
			
		}

		void setCallback(void (*fptr)(void)) { callback = fptr; }
		void setCallback(ClassType& inst, void (ClassType::* fptr)(void)) { callbackList.push_back({ inst, fptr }); }

		virtual void onClick()
		{

			SoundEvent("sfxBtnClick").SendEvent();

			if (callback)
				callback();

			for (auto cb : callbackList)
			{
				(cb.first.*(cb.second))();
			}
		}

	private:
		bool isOverlay{ false };
		void (*callback)(void) { nullptr };
		std::vector<std::pair<ClassType&, void (ClassType::*)(void)>> callbackList;
	};
}