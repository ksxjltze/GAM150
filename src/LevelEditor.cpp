#include "LevelEditor.h"
#include "BasicMeshShape.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "PrimaryMovementController.h"
#include "Serialization.h"

namespace StarBangBang
{

	void HighLightGridNode(Grid& grid)
	{
		AEVec2 mousePos = GetMouseWorldPos();
		A_Node* n = grid.GetNodeFromPosition(mousePos);
		if (n)
			DrawCircle(grid.GetNodeSize() / 2, n->nodePos);
	}

	LevelEditor::LevelEditor(int id, GameStateManager& manager) : Scene(id, manager), serializeTestObj{*(new SerializeTest(0))}
	{
		tileWidth = 100; tileHeight = 100;
		mapWidth = 20, mapHeight = 20;
	}

	LevelEditor::~LevelEditor()
	{
		delete &serializeTestObj;
	}

	void LevelEditor::Load()
	{
		tileObjects.reserve(mapHeight);
		Sprite grassSprite = graphicsManager.CreateSprite(RESOURCES::PROTOTYPE_SPRITE_GRASS_PATH, tileWidth, tileHeight);
		Sprite stoneSprite = graphicsManager.CreateSprite(RESOURCES::PROTOTYPE_SPRITE_STONE_PATH, tileWidth, tileHeight);
		boi				   = graphicsManager.CreateSprite(RESOURCES::PROTOTYPE_SPRITE_1_PATH, tileWidth, tileHeight);

		auto grassTile = std::pair<int, TileSprite>(1, { 1, "Grass", grassSprite });
		auto stoneTile = std::pair<int, TileSprite>(2, { 2, "Stone", stoneSprite });

		palette.insert(grassTile);
		palette.insert(stoneTile);
	}

	void LevelEditor::CreateLevel()
	{
		for (int y = 0; y < mapHeight; y++)
		{
			std::vector<Tile_Old> row;
			row.reserve(mapWidth);

			for (int x = 0; x < mapWidth; x++)
			{
				A_Node* node = grid.GetNode(x, y);
				GameObject* obj = objectManager.NewGameObject();
				objectManager.AddImage(obj, selectedTile.sprite);

				obj->SetPos(node->nodePos);
				Tile_Old tile{ selectedTile , obj };

				node->occupied = true;
				row.push_back(tile);
			}
			tileObjects.push_back(row);
		}
	}

	void LevelEditor::Init()
	{
		grid.CreateGrid(tileWidth, AEVec2{ (f32)mapWidth,(f32)mapHeight });
		selectedTile = palette.at(2);

		LoadLevel();

		camera = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(camera);
		objectManager.AddComponent<PrimaryMovementController>(camera);

	}

	void LevelEditor::Update()
	{
		Scene::Update();

		if (AEInputCheckTriggered(AEVK_1))
		{
			selectedTile = palette.at(1);
			//selectedTile = palette.at("Grass");
		}
		else if (AEInputCheckTriggered(AEVK_2))
		{
			selectedTile = palette.at(2);
			//selectedTile = palette.at("Stone");
		}

		if (AEInputCheckTriggered(AEVK_RETURN))
		{
			SaveLevel();
			Serialization::SaveObject(serializeTestObj);
			//GameObject* serializeTestObj = objectManager.NewGameObject();
			//objectManager.AddImage(serializeTestObj, boi);

			//printf("Saving Game Object\n");
			//objectManager.SaveGameObject(*serializeTestObj);
			//objectManager.DestroyGameObject(serializeTestObj);
		}

		if (AEInputCheckTriggered(AEVK_R))
		{
			LoadLevel();
			Serialization::LoadObject(serializeTestObj);
			//printf("Reading Game Object\n");
			//GameObject* obj = &objectManager.ReadGameObject("../Resources/Test.bin");
			//ImageComponent* image = obj->GetComponent<ImageComponent>();

			//if (image)
			//{
			//	image->SetSprite(boi);
			//}
		}

		//Insert/Replace/Remove Tile.
		AEVec2 mousePos = GetMouseWorldPos();
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			A_Node* n = grid.GetNodeFromPosition(mousePos);
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
			A_Node* n = grid.GetNodeFromPosition(mousePos);
			if (n && n->occupied)
			{
				RemoveTile(n);
			}
		}
	}

	void LevelEditor::InsertTile(A_Node* node)
	{
		GameObject* obj = objectManager.NewGameObject();
		obj->SetPos(node->nodePos);

		Tile_Old tile{ selectedTile , obj };

		objectManager.AddImage(obj, selectedTile.sprite);
		tileObjects[node->index_y][node->index_x] = tile;
		node->occupied = true;
		std::cout << "LevelEditor: TILE INSERTED" << std::endl;
	}

	void LevelEditor::RemoveTile(A_Node* n)
	{
		std::cout << "LevelEditor: NODE OCCUPIED" << std::endl;
		objectManager.DestroyGameObject(tileObjects[n->index_y][n->index_x].gameObject);
		n->occupied = false;
	}

	void LevelEditor::SaveLevel()
	{
		std::ofstream outputStream;
		outputStream.open("../Resources/Levels/test.txt", std::fstream::trunc);
		std::cout << "Saving Level..." << std::endl;

		if (outputStream.is_open())
		{
			for (auto row : tileObjects)	//For Row in Grid (vector<vector<Tile>>)
			{
				for (Tile_Old tile : row)
				{
					outputStream << tile.sprite.id;
				}
				outputStream << std::endl;
			}

			outputStream.close();

		}
	}

	void LevelEditor::LoadLevel()
	{
		std::ifstream inputStream;
		inputStream.open("../Resources/Levels/test.txt");

		if (inputStream.is_open())
		{
			std::string line;
			
			int y = 0;
			while (std::getline(inputStream, line))
			{
				int x = 0;
				std::vector<Tile_Old> row;

				//make this better later
				for (auto c : line)
				{
					Tile_Old tile;

					A_Node* node = grid.GetNode(x++, y);

					tile.sprite.id = c - '0';
					tile.gameObject = objectManager.NewGameObject();
					tile.sprite = palette.at(tile.sprite.id);

					objectManager.AddImage(tile.gameObject, tile.sprite.sprite);
					tile.gameObject->SetPos(node->nodePos);
					node->occupied = true;
					row.push_back(tile);
				}

				y++;
				tileObjects.push_back(row);

			}

			inputStream.close();
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
		Scene::Free();
		grid.FreeGrid();
	}

	void LevelEditor::Unload()
	{
		Scene::Unload();
	}
}

