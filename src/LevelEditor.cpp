#include "LevelEditor.h"
#include "BasicMeshShape.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "Movement.h"
#include "Serialization.h"
#include "PathFinder.h"

namespace StarBangBang
{

	void HighLightGridNode(Grid& grid)
	{
		AEVec2 mousePos = GetMouseWorldPos();
		A_Node* n = grid.GetNodeFromPosition(mousePos);
		if (n)
			DrawCircle(grid.GetNodeSize() / 2, n->nodePos);
	}

	LevelEditor::LevelEditor(int id, GameStateManager& manager) : Scene(id, manager), tileMap{objectManager, graphicsManager}, selectedType{TileType::STONE}
	{
		
	}

	LevelEditor::~LevelEditor()
	{

	}

	void LevelEditor::Load()
	{
		GRAPHICS::SetBackgroundColor(Blue);
	}

	void LevelEditor::Init()
	{
		PathFinder::ShowGrid(false);
		GRAPHICS::SetBackgroundColor(Black);
		
		//filepath = RESOURCES::LEVELS::LEVEL_TEST_PATH;
		filepath = RESOURCES::LEVELS::COLLISION_TEST;

		//TODO: Optimize tile drawing (Low FPS on 100 x 100 tile map)
		if (!LoadLevel(filepath))
		{
			CreateLevel(TILEMAP::DEFAULT_WIDTH, TILEMAP::DEFAULT_WIDTH, TILEMAP::DEFAULT_TILE_SIZE, TileType::BRICK_RED);
			//CreateLevel(30, 30, TILEMAP::DEFAULT_TILE_SIZE, TileType::BRICK_RED);
		}

		//Camera Object
		camera = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(camera);
		objectManager.AddComponent<Movement>(camera);

	}

	void LevelEditor::Update()
	{
		Scene::Update();

		if (AEInputCheckTriggered(AEVK_TAB))
		{
			++selectedType;
		}

		if (AEInputCheckTriggered(AEVK_RETURN))
		{
			SaveLevel(filepath);
		}

		if (AEInputCheckTriggered(AEVK_R))
		{
			//Generate new level
			if (AEInputCheckCurr(AEVK_LSHIFT))
			{
				CreateLevel(TILEMAP::DEFAULT_WIDTH, TILEMAP::DEFAULT_WIDTH, TILEMAP::DEFAULT_TILE_SIZE, selectedType);
			}
			else
				LoadLevel(filepath);
		}

		if (AEInputCheckTriggered(AEVK_SPACE))
		{
			gameStateManager.SetNextGameState(SceneID::MAIN_MENU);
		}

		//Insert/Replace/Remove Tile.
		AEVec2 mousePos = GetMouseWorldPos();
		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			A_Node* n = grid.GetNodeFromPosition(mousePos);
			if (n)
			{
				InsertTile(n);

				//Brush
				//for (auto node : grid.Get4_NodeNeighbours(n))
				//{
				//	InsertTile(node);
				//}
			}
		}

		if (AEInputCheckCurr(AEVK_RBUTTON))
		{
			A_Node* n = grid.GetNodeFromPosition(mousePos);
			if (n)
			{
				RemoveTile(n);
			}
		}
	}

	void LevelEditor::Draw()
	{
		Scene::Draw();
		HighLightGridNode(grid);
		grid.DrawGrid(Black);
	}

	void LevelEditor::Free()
	{
		Scene::Free();
	}

	void LevelEditor::Unload()
	{
		tileMap.Unload();
		Scene::Unload();
	}

	void LevelEditor::InsertTile(A_Node* n)
	{
		tileMap.Insert(n->index_x, n->index_y, selectedType);
	}

	void LevelEditor::RemoveTile(A_Node* n)
	{
		tileMap.Erase(n->index_x, n->index_y);
	}

	void LevelEditor::SaveLevel(const std::string& path)
	{
		tileMap.Save(path);
	}

	bool LevelEditor::LoadLevel(const std::string& path)
	{
		bool success = tileMap.Load(path);
		SetGrid();

		return success;
	}

	void LevelEditor::CreateLevel(int width, int height, float tileSize, TileType type)
	{
		tileMap.Generate(width, height, tileSize, type);
		SetGrid();
	}

	void LevelEditor::SetGrid()
	{
		grid.FreeGrid();
		float scale = tileMap.GetTileScale();
		AEVec2 dimensions = { scale * tileMap.GetMapWidth(), scale * tileMap.GetMapHeight() };
		//grid.CreateGrid(scale, tileMap.GetMapWidth(), tileMap.GetMapHeight(),{ scale / 2, -dimensions.y + scale / 2 });
		grid.CreateGrid(scale, tileMap.GetMapWidth(), tileMap.GetMapHeight(),{ -scale / 2, scale / 2 });
	}

}

