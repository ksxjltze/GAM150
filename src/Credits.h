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
		Credits(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		void NewTextObject(AEVec2 position, const std::string& s, float scale = 1.0f, Color c = White);
		GameObject* cameraObject{ nullptr };
		GameObject* end{ nullptr };
	};

}