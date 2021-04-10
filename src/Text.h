/******************************************************************************/
/*!
\title		Captain Stealth
\file		Text.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Text component.
			Draws text on the screen,
			based on the position of the game object it is attached to.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ComponentCRTP.h"
#include <cstring>
#include "Color.h"

namespace StarBangBang
{
	//Not used
	class TextBox
	{
	public:
		float width = 150.f;
		float height = 150.f;

	};

	class Text: public Component<Text>
	{
	public:
		Text(GameObject* gameObject);
		Text(GameObject* gameObject, const std::string& s, s8 fontId, Color c = White, float scale = 1.0f, bool isWorld = true);
		TextBox textbox;
		s8 fontID;
		/*!*************************************************************************
		 * \brief 
		 * Sets the offset from the game object position.
		 * \param offset 
		 * Vector to offset by.
		***************************************************************************/
		void SetOffset(AEVec2 offset);
		void SetText(const std::string& s);
		void SetTextBox(float width, float height);
		void SetScale(float scale);
		void Start();
		void Draw();
		void SetColor(Color c);
	private:
		AEVec2 offset{ 0, 0 };

		//Whether the text should be drawn based on world position or as a percentage of the screen.
		bool isWorld{ true };

		std::string text;
		float scale;
		Color color;

	};
}