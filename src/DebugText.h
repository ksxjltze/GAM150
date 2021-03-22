#pragma once
#include "Text.h"
#include "ListenerComponent.h"

namespace StarBangBang
{
	class DebugText : public ListenerComponent
	{
	public:
		DebugText(GameObject* obj, s8 fontId = -1);
		void SetFont(s8 fontId);
		void SetTextbox(float width, float height);
		void onNotify(Event e);
		void Update();
		void Draw();
	private:
		float duration;
		float timer;

		s8 fontId;
		std::string text;

		AEVec2 textPos;
		TextBox textbox;
		float fontScale;
	};
}