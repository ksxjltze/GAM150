/******************************************************************************/
/*!
\title		Captain Stealth
\file		LevelEditor.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Level Editor scene.
			Load and Save levels (tilemap).

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "LevelEditor.h"
#include "BasicMeshShape.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include "Movement.h"
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

	/*!*************************************************************************
	 * \brief 
	 * Brush pre-increment operator.
	 * \param mode
	 * Reference to the brush mode to increment.
	 * \return 
	 * Reference to the incremented brush mode.
	***************************************************************************/
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

	/*!*************************************************************************
	 * \brief
	 * Brush post-increment operator.
	 * \param mode
	 * Reference to the brush mode to increment.
	 * \return
	 * Copy of the brush mode before increment.
	***************************************************************************/
	BrushMode operator++(BrushMode& mode, int)
	{
		BrushMode m = mode;
		++mode;
		return m;
	}

	/*!*************************************************************************
	 * \brief 
	 * Highlights the node tha the mouse is hovering over.
	 * \param grid
	 * Reference to the grid of nodes.
	 * \return
	 * void
	***************************************************************************/
	void HighLightGridNode(Grid& grid)
	{
		AEVec2 mousePos = GetMouseWorldPos(true);
		A_Node* n = grid.GetNodeFromPosition(mousePos);
		if (n)
			DrawCircle(grid.GetNodeSize() / 2, n->nodePos);
	}

	/*!*************************************************************************
	 * \brief
	 * Scene Constructor.
	 * \param id
	 * Scene Id
	 * \param manager
	 * Reference to the game state manager.
	***************************************************************************/
	LevelEditor::LevelEditor(int id, GameStateManager& manager) : Scene(id, manager), tileMap{ objectManager, graphicsManager }, selectedType{ TileType::STONE }, brushMode{BrushMode::SINGLE}
	{
		
	}

	/*!*************************************************************************
	 * \brief
	 * Destructor.
	***************************************************************************/
	LevelEditor::~LevelEditor()
	{

	}

	/*!*************************************************************************
	 * \brief
	 * Load.
	 * \return
	 * void
	***************************************************************************/
	void LevelEditor::Load()
	{
		GRAPHICS::SetBackgroundColor(Blue);
	}

	/*!*************************************************************************
	 * \brief
	 * Initializes  the tile map, camera, tile types, etc.
	 * \return
	 * void
	***************************************************************************/
	void LevelEditor::Init()
	{		
		filepath = RESOURCES::LEVELS::LEVEL_GAME_PATH;

		if (!LoadLevel(filepath))
		{
			CreateLevel(TILEMAP::DEFAULT_WIDTH, TILEMAP::DEFAULT_WIDTH, TILEMAP::DEFAULT_TILE_SIZE, TileType::FLOOR_PRISON);
		}

		//Camera Object
		camera = objectManager.NewGameObject();
		CameraComponent& cam = objectManager.AddComponent<CameraComponent>(camera);
		cam.scale = 0.75f;
		cam.EnableZoom(true);
		objectManager.AddComponent<Movement>(camera);

		debugText = objectManager.NewGameObject();
		DebugText& text = objectManager.AddComponent<DebugText>(debugText);
		text.SetTextbox(100, 100);
		text.SetFont(StarBangBang::fontId);

		tileOutline = objectManager.NewGameObject();
		tileImg = objectManager.AddImage(tileOutline, tileMap.tileSet.GetTileSprite(selectedType).sprite);
		tileImg->SetTransparency(0.85f);
	}

	/*!*************************************************************************
	 * \brief
	 * Updates the editor.
	 * \return
	 * void
	***************************************************************************/
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
			//Clear Level
			if (AEInputCheckCurr(AEVK_LSHIFT))
			{
				tileMap.Clear();
			}
			else if (AEInputCheckCurr(AEVK_LCTRL))
			{
				tileMap.Fill(selectedType);
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

		if (n)
		{
			tileOutline->transform.position = n->nodePos;
			tileImg->SetSprite(tileMap.tileSet.GetTileSprite(selectedType).sprite);

			//Debug index pos
			if (AEInputCheckCurr(AEVK_G))
			{
				printf("%d, %d\n", n->index_x, n->index_y);

			}
			else if (AEInputCheckCurr(AEVK_T))
			{
				AEVec2 pos = n->nodePos;
				printf("%f, %f\n", pos.x, pos.y);
			}

			if (AEInputCheckCurr(AEVK_LBUTTON))
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

			if (AEInputCheckCurr(AEVK_RBUTTON))
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

	/*!*************************************************************************
	 * \brief
	 * Draws.
	 * \return
	 * void
	***************************************************************************/
	void LevelEditor::Draw()
	{
		Scene::Draw();
		AEGfxSetBackgroundColor(0.3f, 0.6f, 1.0f);
		HighLightGridNode(grid);

		AEVec2 mousePos = GetMouseWorldPos();
		A_Node* n = grid.GetNodeFromPosition(mousePos);
		if (n)
		{
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
		}

		grid.DrawGrid(Green);

	}

	/*!*************************************************************************
	 * \brief
	 * Frees the tile map.
	 * \return void
	***************************************************************************/
	void LevelEditor::Free()
	{
		Scene::Free();
		grid.FreeGrid();
	}

	/*!*************************************************************************
	 * \brief
	 * Unload.
	 * \return void
	***************************************************************************/
	void LevelEditor::Unload()
	{
		tileMap.Unload();
		Scene::Unload();
	}

	/*!*************************************************************************
	 * \brief
	 * Inserts a tile at the specified node.
	 * \param n
	 * Node to insert at.
	***************************************************************************/
	void LevelEditor::InsertTile(A_Node* n)
	{
		tileMap.Insert(n->index_x, n->index_y, selectedType);
	}

	/*!*************************************************************************
	 * \brief
	 * Removes the tile at the specified node.
	 * \param n
	 * Node to remove tile from.
	***************************************************************************/
	void LevelEditor::RemoveTile(A_Node* n)
	{
		tileMap.Erase(n->index_x, n->index_y);
	}

	/*!*************************************************************************
	 * \brief
	 * Saves the tile map.
	 * \param path
	 * Path to save to.
	 * \return
	 * void
	***************************************************************************/
	void LevelEditor::SaveLevel(const std::string& path)
	{
		tileMap.Save(path);
	}

	/*!*************************************************************************
	 * \brief
	 * Loads the tile map.
	 * \param path
	 * Path to load from.
	 * \return
	 * True if successfully loaded, false otherwise.
	***************************************************************************/
	bool LevelEditor::LoadLevel(const std::string& path)
	{
		bool success = tileMap.Load(path);
		SetGrid();

		return success;
	}

	/*!*************************************************************************
	 * \brief
	 * Generates a level.
	 * \param width
	 * Width of the map.
	 * \param height
	 * Height of the map.
	 * \param tileSize
	 * Size of each tile.
	 * \param type
	 * Type to fill the map with.
	***************************************************************************/
	void LevelEditor::CreateLevel(int width, int height, float tileSize, TileType type)
	{
		tileMap.Generate(width, height, tileSize, type);
		SetGrid();
	}

	/*!*************************************************************************
	 * \brief
	 * Initializes and resets the editor grid.
	***************************************************************************/
	void LevelEditor::SetGrid()
	{
		grid.FreeGrid();
		float scale = tileMap.GetTileScale();
		AEVec2 dimensions = { scale * tileMap.GetMapWidth(), scale * tileMap.GetMapHeight() };
		//grid.CreateGrid(scale, tileMap.GetMapWidth(), tileMap.GetMapHeight(),{ scale / 2, -dimensions.y + scale / 2 });
		grid.CreateGrid(scale, tileMap.GetMapWidth(), tileMap.GetMapHeight(),{ -scale / 2, scale / 2 });
	}

}

