#include "Scene_GameOver.h"
#include "globals.h"
#include "PathFinder.h"
#include "GraphicsManager.h"
#include "UIComponent.h"
#include "Sprite.h"
#include "Click.h"
#include "MusicEvent.h"

namespace StarBangBang
{
	Sprite quitSprite;
	Sprite restartSprite;
}

StarBangBang::Scene_GameOver::Scene_GameOver(int id, GameStateManager& gsm) : Scene(id, gsm)
{
	quitBtn = nullptr;
	restartBtn = nullptr;
}

void StarBangBang::Scene_GameOver::Load()
{
	quitSprite = graphicsManager.CreateSprite(RESOURCES::EXIT1_BUTTON_PATH);
	restartSprite = graphicsManager.CreateSprite(RESOURCES::RESTART_BUTTON_PATH);
}

void StarBangBang::Scene_GameOver::Init()
{
	GRAPHICS::SetZoom(3.0f);

	quitBtn = objectManager.NewGameObject();
	restartBtn = objectManager.NewGameObject();

	objectManager.AddImage(quitBtn, quitSprite);
	objectManager.AddImage(restartBtn, restartSprite);

	quitBtn->transform.scale.x = 1.5f;
	quitBtn->transform.scale.y = 0.75f;
	restartBtn->transform.scale.x = 1.5f;
	restartBtn->transform.scale.y = 0.75f;

	objectManager.AddComponent<Click<Scene_GameOver>>(quitBtn).setCallback(*this, &Scene_GameOver::Quit);
	objectManager.AddComponent<Click<Scene_GameOver>>(restartBtn).setCallback(*this, &Scene_GameOver::Restart);

	quitBtn->transform.position = { 50.0f, -25.0f };
	restartBtn->transform.position = { -50.0f, -25.0f };

	PathFinder::ShowGrid(false);

	(MusicEvent { BGM::GAMEOVER, 1.0f, false }).SendEvent();
}

void StarBangBang::Scene_GameOver::Update()
{
	if (AEInputCheckTriggered(AEVK_ESCAPE))
		Quit();
	else if (AEInputCheckTriggered(AEVK_RETURN))
		Restart();

	Scene::Update();
}

void StarBangBang::Scene_GameOver::Draw()
{
	Scene::Draw();
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	f32 TextWidth, TextHeight;
	float fontScale = 1.0f;

	std::string ggText = "GAME OVER";
	s8* str = const_cast<s8*>(ggText.c_str());

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxGetPrintSize(fontId2, str, fontScale, TextWidth, TextHeight);
	AEGfxPrint(fontId2, str, -TextWidth / 2, 0.6f - TextHeight / 2 , fontScale, 1.0f, 1.0f, 1.0f);
}

void StarBangBang::Scene_GameOver::Free()
{
	Scene::Free();
}

void StarBangBang::Scene_GameOver::Unload()
{
	Scene::Unload();
}

void StarBangBang::Scene_GameOver::Quit()
{
	gameStateManager.SetNextGameState(MAIN_MENU);
}

void StarBangBang::Scene_GameOver::Restart()
{
	gameStateManager.SetNextGameState(GAME);
}
