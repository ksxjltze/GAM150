#include "Logo_Splash.h"
#include "GraphicsManager.h"
#include "globals.h"

using namespace StarBangBang;

struct FadeObj
{

	float alpha = 1.0f;
	Sprite sprite = Sprite();
	float fadeSpeed = 0.3f;
	float duration = 6.0f;
	
	AEVec2 aspect = AEVec2{ 1,1 };
};

using DrawFunc = void (*)(GameStateManager& gsm);
const float delay = 0.5f;

DrawFunc current;
FadeObj digipen_logo;
FadeObj fmod_logo;
bool skipCurrent = false;

float time_past = 0.0f;

float EaseInOutCurve(float t)
{
	return -(cos(PI * t) - 1) / 2;
}


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

StarBangBang::LogoSplash::LogoSplash(int id, GameStateManager& gsm) : Scene(id, gsm)
{

}

void StarBangBang::LogoSplash::Load()
{
	digipen_logo.sprite = graphicsManager.CreateSprite("Resources/Logos/DigiPen_Singapore_WEB_WHITE.png");
	fmod_logo.sprite = graphicsManager.CreateSprite("Resources/Logos/FMOD_Logo.png");

	assert(digipen_logo.sprite.texture);
	assert(digipen_logo.sprite.mesh);
	assert(fmod_logo.sprite.texture);
	assert(fmod_logo.sprite.mesh);
}

void StarBangBang::LogoSplash::Init()
{
	time_past = 0.0f;

	digipen_logo.alpha = 0.5f;
	digipen_logo.aspect = AEVec2{ 5.0f , 1.5f};

	fmod_logo.alpha = 0.5f;
	fmod_logo.aspect = AEVec2{ 3.8f , 1.0f };
	
	current = DrawDigipen;
}

void StarBangBang::LogoSplash::Update()
{

	time_past += g_dt;

	if (time_past > delay)
	{
		//skipCurrent = true;
		gameStateManager.SetNextGameState(SceneID::MAIN_MENU);
		if (AEInputCheckTriggered(VK_ESCAPE) || AEInputCheckTriggered(VK_SPACE) || AEInputCheckTriggered(AEVK_RETURN) ||
			AEInputCheckTriggered(VK_RBUTTON) || AEInputCheckTriggered(VK_LBUTTON))
		{
			skipCurrent = true;
		}
	}
	
}

void StarBangBang::LogoSplash::Draw()
{
	current(gameStateManager);
}

