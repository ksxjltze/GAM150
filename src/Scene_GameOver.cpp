#include "Scene_GameOver.h"
#include "globals.h"
#include "PathFinder.h"
#include "GraphicsManager.h"

StarBangBang::Scene_GameOver::Scene_GameOver(int id, GameStateManager& gsm) : Scene(id, gsm)
{

}

void StarBangBang::Scene_GameOver::Load()
{

}

void StarBangBang::Scene_GameOver::Init()
{
	GameObject* obj = objectManager.NewGameObject();
	obj->transform.scale = { 0.00001f, 0.00001f };
	objectManager.AddImage(obj, graphicsManager.CreateSprite(RESOURCES::BIN_PATH));

	PathFinder::ShowGrid(false);
}

void StarBangBang::Scene_GameOver::Update()
{
	if (AEInputCheckTriggered(AEVK_ESCAPE) || AEInputCheckTriggered(AEVK_RETURN) || AEInputCheckTriggered(AEVK_LBUTTON))
	{
		gameStateManager.SetNextGameState(MAIN_MENU);
	}
}

void StarBangBang::Scene_GameOver::Draw()
{
	Scene::Draw();
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	f32 TextWidth, TextHeight;
	float fontScale = 3.0f;

	std::string ggText = "GAME OVER";
	s8* str = const_cast<s8*>(ggText.c_str());

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxGetPrintSize(fontId, str, fontScale, TextWidth, TextHeight);
	AEGfxPrint(fontId, str, -TextWidth / 2, -TextHeight / 2, fontScale, 1.0f, 1.0f, 1.0f);
}

void StarBangBang::Scene_GameOver::Free()
{
	Scene::Free();
}

void StarBangBang::Scene_GameOver::Unload()
{
	Scene::Unload();
}
