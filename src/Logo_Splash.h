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

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
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

		/*!*************************************************************************
		****
			\brief
				LogoSplash constructor
			\param int
				The scene id
			\param gsm
				The gamestate manager reference
			\return
				void
		****************************************************************************
		***/
		LogoSplash(int id, GameStateManager& gsm);

		/*!*************************************************************************
		****
			\brief
				Splash screen load function
			\param none

			\return
				void
		****************************************************************************
		***/
		void Load();

		/*!*************************************************************************
		****
			\brief
				Splashscreen initialize function
			\param none

			\return
				void
		****************************************************************************
		***/
		void Init();

		/*!*************************************************************************
		****
			\brief
				Splashscreen draw function
			\param none

			\return
				void
		****************************************************************************
		***/
		void Draw();

		/*!*************************************************************************
		****
			\brief
				Splashscreen update function
			\param none

			\return
				void
		****************************************************************************
		***/
		void Update();


	};
}