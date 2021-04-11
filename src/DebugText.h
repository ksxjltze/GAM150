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

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
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
		/*!*************************************************************************
		 * \brief Component Constructor.
		 * 
		 * \param obj GameObject to attach to.
		 * \param fontId Font to use for text rendering.
		***************************************************************************/
		DebugText(GameObject* obj, s8 fontId = -1);

		/*!*************************************************************************
		 * \brief 
		 * Sets the font to use for text rendering.
		 * \param fontId FontId to use for text rendering.
		***************************************************************************/
		void SetFont(s8 fontId);

		/*!*************************************************************************
		 * \brief 
		 * Sets the textbox dimensions.
		 * \param width Textbox Width
		 * \param height Textbox Height
		***************************************************************************/
		void SetTextbox(float width, float height);

		/*!*************************************************************************
		 * \brief 
		 * Listener callback. Invoked when an event is received from the Message Bus.
		 * Listens for a PRINT_TEXT event.
		 * \param e Event data.
		***************************************************************************/
		void onNotify(Event e);

		/*!*************************************************************************
		 * \brief 
		 * Update function. Called once per frame.
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief 
		 * Draw function. Called once per frame.
		***************************************************************************/
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