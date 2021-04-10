/******************************************************************************/
/*!
\title		Captain Stealth
\file		Scene_GameOver.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		GameOver scene.
			Displayed when the player loses the game.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "State.h"

namespace StarBangBang
{
	class Scene_GameOver : public Scene
	{
	public:
		Scene_GameOver(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		void Quit();
		void Restart();
		GameObject* quitBtn;
		GameObject* restartBtn;
	};

}