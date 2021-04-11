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
		/*!*************************************************************************
		 * \brief 
		 * Component Constructor.
		 * Attaches the component to a game object.
		 * \param gameObject
		 * GameObject to attach to.
		***************************************************************************/
		Text(GameObject* gameObject);

		/*!*************************************************************************
		 * \brief 
		 * Component Constructor.
		 * Attaches the component to a game object.
		 * Sets the text string, font, color and scale of the text object.
		 * 
		 * \param gameObject
		 * GameObject to attach to.
		 * 
		 * \param textString
		 * String to display.
		 * 
		 * \param fontId
		 * Font to use.
		 * 
		 * \param textColor
		 * Color of the text.
		 * 
		 * \param textScale
		 * Scale of the text.
		 * 
		 * \param isWorld
		 * Whether the text object should use world position or screen position (Percentage)
		***************************************************************************/
		Text(GameObject* gameObject, const std::string& textString, s8 fontId, Color textColor = White, float textScale = 1.0f, bool isWorld = true);

		/*!*************************************************************************
		 * \brief 
		 * Sets the offset from the game object position.
		 * \param offset 
		 * Vector to offset by.
		***************************************************************************/
		void SetOffset(AEVec2 offset);

		/*!*************************************************************************
		 * \brief 
		 * Sets the text to display.
		 * \param textString
		 * String to display.
		***************************************************************************/
		void SetText(const std::string& textString);

		/*!*************************************************************************
		 * \brief 
		 * Sets the textbox dimensions.
		 * \param width Width of the textbox.
		 * \param height Height of the textbox.
		***************************************************************************/
		void SetTextBox(float width, float height);

		/*!*************************************************************************
		 * \brief 
		 * Sets the scale of the text.
		 * \param textScale
		 * Scale of the text.
		***************************************************************************/
		void SetScale(float textScale);

		/*!*************************************************************************
		 * \brief 
		 * Start function. Called once at the start of the scene.
		***************************************************************************/
		void Start();
		
		/*!*************************************************************************
		 * \brief 
		 * Draw function. Called once every frame.
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief 
		 * Sets the color of the text.
		 * \param textColor
		 * Color to set.
		***************************************************************************/
		void SetColor(Color textColor);

		TextBox textbox;
		s8 fontID;
	private:
		AEVec2 offset{ 0, 0 };

		//Whether the text should be drawn based on world position or as a percentage of the screen.
		bool isWorld{ true };

		std::string text;
		float scale;
		Color color;

	};
}