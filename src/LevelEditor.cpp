#include "LevelEditor.h"
#include "BasicMeshShape.h"
#include "Utils.h"

namespace StarBangBang
{
	void HighLightGridNode(Grid& grid)
	{
		AEVec2 mousePos = GetMouseWorldPos();
		Node* n = grid.GetNodeFromPosition(mousePos);
		if (n)
			DrawCircle(grid.GetNodeSize() / 2, n->nodePos);
	}

	LevelEditor::LevelEditor(int id, GameStateManager& manager) : Scene(id, manager)
	{
		tileWidth = 50; tileHeight = 50;
	}

	void LevelEditor::Load()
	{
		Sprite grassSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_GRASS_PATH, tileWidth, tileHeight);
		Sprite stoneSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_STONE_PATH, tileWidth, tileHeight);

		std::pair<std::string, Sprite> grassTile = std::pair<std::string, Sprite>("Grass", grassSprite);
		std::pair<std::string, Sprite> stoneTile = std::pair<std::string, Sprite>("Stone", stoneSprite);

		palette.insert(grassTile);
		palette.insert(stoneTile);
	}

	void LevelEditor::Init()
	{
		GameObject* obj = objectManager.NewGameObject();
		GameObject* obj2 = objectManager.NewGameObject();

		objectManager.AddImage(obj, palette.at("Grass"));
		objectManager.AddImage(obj2, palette.at("Stone"));

		obj2->transform.position.x += tileWidth;
		grid.CreateGrid(tileWidth, 20, 20);

		tileObjects.push_back(obj);
		tileObjects.push_back(obj2);
	}

	void LevelEditor::Update()
	{
		Scene::Update();
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			AEVec2 mousePos = GetMouseWorldPos();
			Node* n = grid.GetNodeFromPosition(mousePos);
			if (n)
			{
				GameObject* obj = objectManager.NewGameObject();
				obj->SetPos(n->nodePos);
				objectManager.AddImage(obj, palette.at("Grass"));
				tileObjects.push_back(obj);
			}
		}
	}

	void LevelEditor::Draw()
	{
		Scene::Draw();
		HighLightGridNode(grid);
		grid.DrawGrid();
	}

	void LevelEditor::Free()
	{
	}

	void LevelEditor::Unload()
	{
	}
}

