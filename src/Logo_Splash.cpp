#include "Logo_Splash.h"
#include "GraphicsManager.h"
#include "globals.h"

using namespace StarBangBang;

struct FadeObj
{

	float alpha = 1.0f;
	Sprite sprite = Sprite();
	float fadeSpeed = 0.2f;
	float duration = 5.5f;

};

using DrawFunc = void (*)(GameStateManager& gsm);


DrawFunc current;

FadeObj digipen_logo;
FadeObj fmod_logo;
bool skipCurrent = false;

void DrawFmod(GameStateManager& gsm)
{

	AEVec2 screenScale = GRAPHICS::GetScreenScale();


	AEVec2 scale{ 1.0f * 5.0f / screenScale.x ,1.0f * 2.0f  / screenScale.y};
	GRAPHICS::SetBackgroundColor(Black);

	
	StarBangBang::GRAPHICS::DrawImage(fmod_logo.sprite.mesh, fmod_logo.sprite.texture, White, 
		AEVec2{ 0,0 }, scale , 0.0f, fmod_logo.alpha);


	fmod_logo.duration -= StarBangBang::g_dt;
	fmod_logo.alpha -= StarBangBang::g_dt * fmod_logo.fadeSpeed;

	if (fmod_logo.duration < 0.0f || skipCurrent)
	{
		gsm.SetNextGameState(SceneID::MAIN_MENU);
		skipCurrent = false;
	}

}

void DrawDigipen(GameStateManager& gsm)
{
	AEVec2 screenScale = GRAPHICS::GetScreenScale();


	AEVec2 scale{ 1.0f * 5.0f / screenScale.x ,1.0f * 2.0f / screenScale.y };

	GRAPHICS::SetBackgroundColor(Black);

	StarBangBang::GRAPHICS::DrawImage(digipen_logo.sprite.mesh, digipen_logo.sprite.texture, White, 
		AEVec2{ 0,0 }, scale , 0.0f, digipen_logo.alpha);
	

	digipen_logo.duration -= StarBangBang::g_dt;
	digipen_logo.alpha -= StarBangBang::g_dt * digipen_logo.fadeSpeed;
	AEGfxSetTransparency(digipen_logo.alpha);

	if (digipen_logo.duration < 0.0f || skipCurrent)
	{
		current = DrawFmod;
		skipCurrent = false;
	}
}

StarBangBang::LogoSplash::LogoSplash(int id, GameStateManager& gsm) : Scene(id, gsm)
{

}

void StarBangBang::LogoSplash::Load()
{
	digipen_logo.sprite = graphicsManager.CreateSprite("Resources/Logos/DigiPen_WHITE.png");
	fmod_logo.sprite = graphicsManager.CreateSprite("Resources/Logos/FMOD_Logo.png");

	assert(digipen_logo.sprite.texture);
	assert(digipen_logo.sprite.mesh);
	assert(fmod_logo.sprite.texture);
	assert(fmod_logo.sprite.mesh);


	
}

void StarBangBang::LogoSplash::Init()
{

	digipen_logo.alpha = 1.0f;
	digipen_logo.fadeSpeed = 0.2f;
	digipen_logo.duration = 5.5f;

	fmod_logo.alpha = 1.0f;
	fmod_logo.duration = 5.5f;
	fmod_logo.fadeSpeed = 0.2f;

	
	current = DrawDigipen;
	
}

void StarBangBang::LogoSplash::Update()
{
	if (AEInputCheckTriggered(VK_ESCAPE) || AEInputCheckTriggered(VK_SPACE)
		|| AEInputCheckTriggered(VK_RBUTTON) || AEInputCheckTriggered(VK_LBUTTON))
	{
		skipCurrent = true;
	}
}

void StarBangBang::LogoSplash::Draw()
{
	current(gameStateManager);
}

