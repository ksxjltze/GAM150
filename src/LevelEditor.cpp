#include "LevelEditor.h"
#include "BasicMeshShape.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

#include "PrimaryMovementController.h"

namespace StarBangBang
{
	//typedef std::pair<std::string, Sprite> TileImage;
	//typedef std::pair<Node*, GameObject*> Tile;

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
		mapWidth = 20, mapHeight = 20;
	}

	void LevelEditor::Load()
	{
		tileObjects.reserve(mapHeight);
		Sprite grassSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_GRASS_PATH, tileWidth, tileHeight);
		Sprite stoneSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_STONE_PATH, tileWidth, tileHeight);

		auto grassTile = std::pair<std::string, TileSprite>("Grass", { 1, "Grass", grassSprite });
		auto stoneTile = std::pair<std::string, TileSprite>("Stone", { 2, "Stone", stoneSprite });

		palette.insert(grassTile);
		palette.insert(stoneTile);
	}

	void LevelEditor::Init()
	{
		grid.CreateGrid(tileWidth, mapWidth, mapHeight);
		selectedTile = palette.at("Stone");

		for (int y = 0; y < mapHeight; y++)
		{
			std::vector<Tile> row;
			row.reserve(mapWidth);

			for (int x = 0; x < mapWidth; x++)
			{
				Node* node = grid.GetNode(x, y);
				GameObject* obj = objectManager.NewGameObject();
				objectManager.AddImage(obj, selectedTile.sprite);

				obj->SetPos(node->nodePos);
				Tile tile{ selectedTile , obj };

				node->occupied = true;
				row.push_back(tile);
			}
			tileObjects.push_back(row);
		}

		camera = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(camera);
		objectManager.AddComponent<PrimaryMovementController>(camera);

	}

	void LevelEditor::Update()
	{
		Scene::Update();

		if (AEInputCheckTriggered(AEVK_1))
		{
			selectedTile = palette.at("Grass");
		}
		else if (AEInputCheckTriggered(AEVK_2))
		{
			selectedTile = palette.at("Stone");
		}

		if (AEInputCheckTriggered(AEVK_RETURN))
		{
			SaveLevel();
		}

		//Insert/Replace/Remove Tile.
		AEVec2 mousePos = GetMouseWorldPos();
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			Node* n = grid.GetNodeFromPosition(mousePos);
			if (n)
			{

				if (!n->occupied)
				{
					InsertTile(n);
				}
				else
				{
					RemoveTile(n);
					InsertTile(n);
				}
			}
		}

		if (AEInputCheckTriggered(AEVK_RBUTTON))
		{
			Node* n = grid.GetNodeFromPosition(mousePos);
			if (n->occupied)
			{
				RemoveTile(n);
			}
		}
	}

	void LevelEditor::InsertTile(Node* node)
	{
		GameObject* obj = objectManager.NewGameObject();
		obj->SetPos(node->nodePos);

		Tile tile{ selectedTile , obj };

		objectManager.AddImage(obj, selectedTile.sprite);
		tileObjects[node->index_y][node->index_x] = tile;
		node->occupied = true;
		std::cout << "LevelEditor: TILE INSERTED" << std::endl;
	}

	void LevelEditor::RemoveTile(Node* n)
	{
		std::cout << "LevelEditor: NODE OCCUPIED" << std::endl;
		objectManager.DestroyGameObject(tileObjects[n->index_y][n->index_x].gameObject);
		n->occupied = false;
	}

	void LevelEditor::SaveLevel()
	{
		std::fstream outputStream;
		outputStream.open("../Resources/Levels/test.txt", std::fstream::out);
		std::cout << "Saving Level..." << std::endl;

		for (auto row : tileObjects)
		{
			for (Tile tile : row)
			{
				outputStream << tile.sprite.id;
			}
			outputStream << std::endl;
		}

		outputStream.close();
	}

	void LevelEditor::Draw()
	{
		Scene::Draw();
		HighLightGridNode(grid);
		grid.DrawGrid();
	}

	void LevelEditor::Free()
	{
		Scene::Free();
		grid.FreeGrid();
	}

	void LevelEditor::Unload()
	{
		Scene::Unload();
	}
}

