/******************************************************************************/
/*!
\title		Captain Stealth
\file		Logo_Splash.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the declaration for Logo_Splash.cpp
			Implements a Logo splash scene 

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "GameStateManager.h"



namespace StarBangBang
{
	//logo scene class
	class LogoSplash : public Scene
	{
	public:
		
		LogoSplash(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Draw();
		void Update();


	};
}