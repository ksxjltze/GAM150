#include "MapEditor.h"

StarBangBang::MapEditor::MapEditor(GameStateManager* manager, int id) : State(id)
{
	gameStateManager = manager;
	tileMap = nullptr;
}

void StarBangBang::MapEditor::Load()
{
	tileManager.Load(graphicsManager);
}

void StarBangBang::MapEditor::Init()
{
	tileMap = tileManager.Init(objectManager, graphicsManager);
	//objectManager.AddDragComponent(tileMap);
}

void StarBangBang::MapEditor::Update()
{
	tileMap->transform.position.x += 10 * AEFrameRateControllerGetFrameTime();
	objectManager.Update();
}

void StarBangBang::MapEditor::Draw()
{
	objectManager.Draw();
}

void StarBangBang::MapEditor::Free()
{
	objectManager.FreeComponents();
	objectManager.FreeObjects();
}

void StarBangBang::MapEditor::Unload()
{
	graphicsManager.UnloadTextures();
	graphicsManager.FreeMeshes();
}
