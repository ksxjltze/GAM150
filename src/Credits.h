/******************************************************************************/
/*!
\title		Captain Stealth
\file		Credits.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Credits scene.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "State.h"

namespace StarBangBang
{
	class Credits : public Scene
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Scene constructor.
		 * \param id
		 * Scene Id
		 * \param gsm
		 * Reference to the game state manager
		***************************************************************************/
		Credits(int id, GameStateManager& gsm);

		/*!*************************************************************************
		 * \brief 
		 * Load.
		 * \return
		 * void
		***************************************************************************/
		void Load();

		/*!*************************************************************************
		 * \brief
		 * Init.
		 * \return
		 * void
		***************************************************************************/
		void Init();

		/*!*************************************************************************
		 * \brief
		 * Update.
		 * \return
		 * void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief
		 * Draw.
		 * \return
		 * void
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief
		 * Free.
		 * \return
		 * void
		***************************************************************************/
		void Free();

		/*!*************************************************************************
		 * \brief
		 * Unload.
		 * \return
		 * void
		***************************************************************************/
		void Unload();
	private:

		/*!*************************************************************************
		 * \brief 
		 * Creates a new text object.
		 * \param position
		 * Position to place the object.
		 * \param textString
		 * Text to display.
		 * \param scale
		 * Scale of the text.
		 * \param textColor
		 * Color of the text
		***************************************************************************/
		void NewTextObject(AEVec2 position, const std::string& textString, float scale = 1.0f, Color textColor = White);
		GameObject* cameraObject{ nullptr };
		GameObject* end{ nullptr };
	};

}