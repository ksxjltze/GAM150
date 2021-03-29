#include "LevelEditor.h"
#include "BasicMeshShape.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "Movement.h"
#include "Serialization.h"
#include "PathFinder.h"
#include "globals.h"
#include <sstream>

namespace StarBangBang
{

	enum class BrushMode { SINGLE, CROSS, SQUARE, END };
	static const std::map<BrushMode, const std::string> brushNames
	{
		{BrushMode::SINGLE, "SINGLE"}, {BrushMode::CROSS, "CROSS"}, {BrushMode::SQUARE, "SQUARE"}
	};

	BrushMode& operator++(BrushMode& mode)
	{
		BrushMode m = BrushMode(static_cast<int>(mode) + 1);
		if (m >= BrushMode::END)
		{
			m = BrushMode::SINGLE;
		}

		mode = m;
		return mode;
	}

	BrushMode operator++(BrushMode& mode, int)
	{
		BrushMode m = mode;
		++mode;
		return m;
	}

	void HighLightGridNode(Grid& grid)
	{
		AEVec2 mousePos = GetMouseWorldPos();
		A_Node* n = grid.GetNodeFromPosition(mousePos);
		if (n)
			DrawCircle(grid.GetNodeSize() / 2, n->nodePos);
	}

	LevelEditor::LevelEditor(int id, GameStateManager& manager) : Scene(id, manager), tileMap{ objectManager, graphicsManager }, selectedType{ TileType::STONE }, brushMode{BrushMode::SINGLE}
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
		PathFinder::PathFinderInit();
		PathFinder::ShowGrid(false);
		GRAPHICS::SetBackgroundColor(Black);
		
		filepath = RESOURCES::LEVELS::LEVEL_TEST_PATH;
		//filepath = RESOURCES::LEVELS::COLLISION_TEST;

		//TODO: Optimize tile drawing (Low FPS on 100 x 100 tile map)
		if (!LoadLevel(filepath))
		{
			CreateLevel(TILEMAP::DEFAULT_WIDTH, TILEMAP::DEFAULT_WIDTH, TILEMAP::DEFAULT_TILE_SIZE, TileType::FLOOR_PRISON);
			//CreateLevel(30, 30, TILEMAP::DEFAULT_TILE_SIZE, TileType::FLOOR_PRISON);
		}

		//Camera Object
		camera = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(camera).scale = 0.75f;
		objectManager.AddComponent<Movement>(camera);

		debugText = objectManager.NewGameObject();
		DebugText& text = objectManager.AddComponent<DebugText>(debugText);
		text.SetTextbox(100, 100);
		text.SetFont(StarBangBang::fontId);

		tileOutline = objectManager.NewGameObject();
		tileImg = objectManager.AddImage(tileOutline, tileMap.tileSet.GetTileSprite(selectedType).sprite);
		tileImg->SetTransparency(0.9f);

	}

	void LevelEditor::Update()
	{
		Scene::Update();

		if (AEInputCheckTriggered(AEVK_TAB))
		{
			++selectedType;
			MessageBus::Notify({ EventId::PRINT_TEXT, std::string("TILE TYPE CHANGED: ") + tileMap.tileSet.GetTileTypeName(selectedType) });
		}

		if (AEInputCheckTriggered(AEVK_Q))
		{
			++brushMode;
			std::string text{ "BRUSH CHANGED: " };
			text += brushNames.at(brushMode);
			MessageBus::Notify({ EventId::PRINT_TEXT, text});
		}

		if (AEInputCheckTriggered(AEVK_F))
		{
			grid.ToggleVisible();
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

		if (AEInputCheckTriggered(AEVK_ESCAPE))
		{
			gameStateManager.SetNextGameState(SceneID::MAIN_MENU);
		}

		//Insert/Replace/Remove Tile.
		AEVec2 mousePos = GetMouseWorldPos();
		A_Node* n = grid.GetNodeFromPosition(mousePos);

		tileOutline->transform.position = n->nodePos;
		tileImg->SetSprite(tileMap.tileSet.GetTileSprite(selectedType).sprite);

		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			if (n)
			{
				//Brush
				InsertTile(n);
				switch (brushMode)
				{
				case BrushMode::CROSS:
					for (auto node : grid.Get4_NodeNeighbours(n))
					{
						InsertTile(node);
					}
					break;
				case BrushMode::SQUARE:
					for (auto node : grid.Get8_NodeNeighbours(n))
					{
						InsertTile(node);
					}
					break;
				}
			}
		}

		if (AEInputCheckCurr(AEVK_RBUTTON))
		{
			if (n)
			{
				RemoveTile(n);
				//Brush
				switch (brushMode)
				{
				case BrushMode::CROSS:
					for (auto node : grid.Get4_NodeNeighbours(n))
					{
						RemoveTile(node);
					}
					break;
				case BrushMode::SQUARE:
					for (auto node : grid.Get8_NodeNeighbours(n))
					{
						RemoveTile(node);
					}
					break;
				}
			}

		}
	}

	void LevelEditor::Draw()
	{
		Scene::Draw();
		AEGfxSetBackgroundColor(0.3f, 0.6f, 1.0f);
		HighLightGridNode(grid);

		AEVec2 mousePos = GetMouseWorldPos();
		A_Node* n = grid.GetNodeFromPosition(mousePos);
		switch (brushMode)
		{
		case BrushMode::CROSS:
			for (auto node : grid.Get4_NodeNeighbours(n))
			{
				tileImg->Draw(node->nodePos);
			}
			break;
		case BrushMode::SQUARE:
			for (auto node : grid.Get8_NodeNeighbours(n))
			{
				tileImg->Draw(node->nodePos);
			}
			break;
		}

		grid.DrawGrid(Green);

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

