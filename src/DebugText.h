/******************************************************************************/
/*!
\title		Captain Stealth
\file		DebugText.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Debug Text Component.
			Displays "Floating" text on the screen when it receives
			the PRINT_TEXT event.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

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
		float fadeStart;
		float timer;

		s8 fontId;
		std::string text;

		AEVec2 textPos;
		TextBox textbox;
		float fontScale;
	};
}