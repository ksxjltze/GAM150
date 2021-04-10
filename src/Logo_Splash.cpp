/******************************************************************************/
/*!
\title		Captain Stealth
\file		Logo_Splash.cpp
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the definition for Logo_Splash.h
			Implements a Logo splash scene

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#include "Logo_Splash.h"
#include "GraphicsManager.h"
#include "globals.h"

using namespace StarBangBang;

//fade object struct for logos
struct FadeObj
{

	float alpha = 1.0f;
	Sprite sprite = Sprite();
	float fadeSpeed = 0.3f;
	float duration = 6.0f;
	
	AEVec2 aspect = AEVec2{ 1,1 };
};


using DrawFunc = void (*)(GameStateManager& gsm);

//minimum input delay for skip
const float delay = 0.5f;

//the current draw function
DrawFunc current;
FadeObj digipen_logo;
FadeObj fmod_logo;

//skip current scene
bool skipCurrent = false;

float time_past = 0.0f;



/*!*************************************************************************
****
	\brief
		A ease curve function that returns a corresponding value given a time
	\param t
		The time value
	\return
		The resulting value
****************************************************************************
***/
float EaseInOutCurve(float t)
{
	return -(cos(PI * t) - 1) / 2;
}

/*!*************************************************************************
****
	\brief
		Handles the drawing of FMOD logo
	\param gsm
		The gamestate manager reference
	\return
		void
****************************************************************************
***/
void DrawFmod(GameStateManager& gsm)
{


	fmod_logo.alpha = EaseInOutCurve(time_past * fmod_logo.fadeSpeed);

	AEVec2 screenScale = GRAPHICS::GetScreenScale();


	AEVec2 aspect_scale{ fmod_logo.aspect.x / screenScale.x , fmod_logo.aspect.y / screenScale.y};
	GRAPHICS::SetBackgroundColor(Black);

	
	StarBangBang::GRAPHICS::DrawImage(fmod_logo.sprite.mesh, fmod_logo.sprite.texture, White, 
		AEVec2{ 0,0 }, aspect_scale, 0.0f, fmod_logo.alpha);


	fmod_logo.duration -= StarBangBang::g_dt;

	if (fmod_logo.duration < 0.0f || skipCurrent)
	{
		time_past = 0.0f;
		gsm.SetNextGameState(SceneID::MAIN_MENU);
		skipCurrent = false;
	}

}

/*!*************************************************************************
****
	\brief
		Handles the drawing of Digipen logo
	\param gsm
		The gamestate manager reference
	\return
		void
****************************************************************************
***/
void DrawDigipen(GameStateManager&)
{

	digipen_logo.alpha = EaseInOutCurve(time_past * digipen_logo.fadeSpeed);
	
	AEVec2 screenScale = GRAPHICS::GetScreenScale();


	AEVec2 aspect_scale{ digipen_logo.aspect.x / screenScale.x , digipen_logo.aspect.y / screenScale.y };

	GRAPHICS::SetBackgroundColor(Black);

	StarBangBang::GRAPHICS::DrawImage(digipen_logo.sprite.mesh, digipen_logo.sprite.texture, White, 
		AEVec2{ 0,0 }, aspect_scale, 0.0f, digipen_logo.alpha);
	
	
	digipen_logo.duration -= StarBangBang::g_dt;
	

	if (digipen_logo.duration < 0.0f || skipCurrent)
	{
		time_past = 0.0f;
		current = DrawFmod;
		skipCurrent = false;
	}

}

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
StarBangBang::LogoSplash::LogoSplash(int id, GameStateManager& gsm) : Scene(id, gsm)
{

}

/*!*************************************************************************
****
	\brief
		Gamestate load function
	\param none

	\return
		void
****************************************************************************
***/
void StarBangBang::LogoSplash::Load()
{
	digipen_logo.sprite = graphicsManager.CreateSprite("Resources/Logos/DigiPen_Singapore_WEB_WHITE.png");
	fmod_logo.sprite = graphicsManager.CreateSprite("Resources/Logos/FMOD_Logo.png");

	assert(digipen_logo.sprite.texture);
	assert(digipen_logo.sprite.mesh);
	assert(fmod_logo.sprite.texture);
	assert(fmod_logo.sprite.mesh);
}

/*!*************************************************************************
****
	\brief
		Gamestate initialize function
	\param none

	\return
		void
****************************************************************************
***/
void StarBangBang::LogoSplash::Init()
{
	time_past = 0.0f;

	digipen_logo.alpha = 0.5f;
	digipen_logo.aspect = AEVec2{ 5.0f , 1.5f};

	fmod_logo.alpha = 0.5f;
	fmod_logo.aspect = AEVec2{ 3.8f , 1.0f };
	
	current = DrawDigipen;
}

/*!*************************************************************************
****
	\brief
		Gamestate update function
	\param none

	\return
		void
****************************************************************************
***/
void StarBangBang::LogoSplash::Update()
{

	time_past += g_dt;

	if (time_past > delay)
	{
		if (AEInputCheckTriggered(VK_ESCAPE) || AEInputCheckTriggered(VK_SPACE) || AEInputCheckTriggered(AEVK_RETURN) ||
			AEInputCheckTriggered(VK_RBUTTON) || AEInputCheckTriggered(VK_LBUTTON))
		{
			//skipCurrent = true;
			gameStateManager.SetNextGameState(MAIN_MENU);
		}
	}
	
}

/*!*************************************************************************
****
	\brief
		Gamestate draw function
	\param none

	\return
		void
****************************************************************************
***/
void StarBangBang::LogoSplash::Draw()
{
	current(gameStateManager);
}

