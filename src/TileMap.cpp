/******************************************************************************/
/*!
\title		Captain Stealth
\file		TileMap.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		TileMap class.
			Responsible for loading tiles from the level data file.
			Or generating new tile maps.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#include <fstream>
#include "constants.h"
#include "TileMap.h"

namespace StarBangBang
{

	/*!*************************************************************************
	 * \brief
	 * TileMap Constructor.
	 * \param objM
	 * Reference to the scene's object manager.
	 * \param gfxM
	 * Reference to the scene's graphics manager.
	***************************************************************************/
	TileMap::TileMap(ObjectManager& objM, GraphicsManager& gfxM) : scale{ 1.0f }, mapWidth{ 0 }, mapHeight{ 0 }, objMgr{ objM }, gfxMgr{ gfxM }, base{ nullptr }
	{
		
	}

	/*!*************************************************************************
	 * \brief
	 * Init function.
	 * Loads the tile set and creates the game object for the tile map.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Init()
	{
		if (!base)
		{
			tileSet.Load(gfxMgr);
			base = objMgr.NewGameObject();
		}

	}

	/*!*************************************************************************
	 * \brief
	 * Generates a new tile map.
	 * \param width
	 * Width of the tile map.
	 * \param height
	 * Height of the tile map.
	 * \param tileSize
	 * Size of each tile.
	 * \param type
	 * Tile Type to fill the new map.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Generate(int width, int height, float tileSize, TileType type)
	{
		Clear();
		//Default sprite
		TileSprite tileSprite = tileSet.GetTileSprite(type);

		mapWidth = width;
		mapHeight = height;
		scale = tileSize;

		AEVec2 offset = GetCentreOffset();

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				std::pair<int, int> index = { x, y};
				AEVec2 pos = { x * scale - offset.x, y * scale - offset.y };

				Tile tile = CreateNewTile(pos, tileSprite);
				map.insert({ index, tile });
			}
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Validates if the file is valid for loading.
	 * \param is
	 * Input file stream Reference.
	 * \param widthStr
	 * Width Tag string to check against.
	 * \param heightStr
	 * Height Tag string to check against.
	 * \param sizeStr
	 * Size Tag string to check against.
	 * \return
	 * True if valid, false otherwise
	***************************************************************************/
	bool StarBangBang::TileMap::ValidateFile(std::ifstream& is, std::string& widthStr, std::string& heightStr, std::string& sizeStr)
	{
		is >> widthStr;

		if (widthStr.find(STRING_TAGS::TILEMAP_WIDTH_TAG) == widthStr.npos)
		{
			fprintf(stderr, "TileMap: Error Reading Width!\n");
			return false;
		}

		is >> widthStr;

		//Height
		is >> heightStr;

		if (heightStr.find(STRING_TAGS::TILEMAP_HEIGHT_TAG) == heightStr.npos)
		{
			fprintf(stderr, "TileMap: Error Reading Height!\n");
			return false;
		}

		is >> heightStr;

		//Size
		std::string temp;
		is >> sizeStr;
		is >> temp;

		sizeStr += ' ' + temp;

		if (sizeStr.find(STRING_TAGS::TILEMAP_SIZE_TAG) == sizeStr.npos)
		{
			fprintf(stderr, "TileMap: Error Reading Tile Size!\n");
			return false;
		}

		is >> sizeStr;

		widthStr = widthStr.substr(widthStr.find_first_not_of(STRING_TAGS::TILEMAP_WIDTH_TAG + ' '));
		heightStr = heightStr.substr(heightStr.find_first_not_of(STRING_TAGS::TILEMAP_HEIGHT_TAG + ' '));
		sizeStr = sizeStr.substr(heightStr.find_first_not_of(STRING_TAGS::TILEMAP_SIZE_TAG + ' '));

		return true;
	}

	/*!*************************************************************************
	 * \brief
	 * Saves the tile map to the specified path.
	 * \param path
	 * File path to save to.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Save(std::string path)
	{
		std::ofstream os;
		os.open(path);
		
		if (os.is_open())
		{
			printf("Tilemap: SAVING LEVEL\n");
			os << "Width: " << mapWidth << std::endl;
			os << "Height: " << mapHeight << std::endl;
			os << "Tile Size: " << scale << std::endl;

			for (int y = mapHeight - 1; y >= 0; --y)
			{
				for (int x = 0; x < mapWidth; ++x)
				{
					std::pair<int, int> pos = { x, y };
					if (map.find(pos) != map.end())
					{
						const Tile& tile = map.at(pos);
						os << static_cast<int>(tile.type);
					}
					else
					{
						os << static_cast<int>(TileType::NONE);
					}

					if (x < mapWidth - 1)
						os << ',';
				}
				os << std::endl;
			}
			os.close();
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Loads the tile map from the specified path.
	 * \param path
	 * File path to load from.
	***************************************************************************/
	bool StarBangBang::TileMap::Load(std::string path)
	{
		Init();
		std::ifstream is;
		is.open(path);

		if (is.is_open())
		{
			Clear();

			std::string widthStr, heightStr, sizeStr;
			if (!ValidateFile(is, widthStr, heightStr, sizeStr))
				return false;

			mapWidth = atoi(widthStr.c_str());
			mapHeight = atoi(heightStr.c_str());
			scale = static_cast<float>(atof(sizeStr.c_str()));

			//Centre TileMap
			AEVec2 offset = GetCentreOffset();

			int y { mapHeight - 1 };

			while (!is.eof())
			{
				int x {0};
				std::string row;
				is >> row;

				for (auto ch = row.begin(); ch != row.end(); ch++)
				{
					std::string typeString;

					//Assuming CSV Format
					//Reads data from each cell
					while (*ch != ',')
					{
						typeString += *ch;
						if (ch + 1 != row.end())
							++ch;
						else
							break;
					}
					
					//Determine Tile Type
					int typeID = atoi(typeString.c_str());
					TileType type = static_cast<TileType>(typeID);

					if (type != TileType::NONE)
					{
						Insert(x++, y, type);
					}
					else
						++x;

				}
				--y;

			}
			is.close();
			return true;
		}
		else
		{
			fprintf(stderr, "TileMap: ERROR OPENING FILE\n");
			return false;
		}
	}


	/*!*************************************************************************
	 * \brief
	 * Clears the tile map.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Clear()
	{
		//Clear map
		if (!map.empty())
		{
			using coords = std::pair<int, int>;
			for (const std::pair<coords, Tile>& tile : map)
			{
				tile.second.spriteObject->gameObject->SetActive(false);
			}
			map.clear();
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Fills the tile map with the specified tile type.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Fill(TileType type)
	{
		if (!map.empty())
		{
			TileSprite s = tileSet.GetTileSprite(type);
			using coords = std::pair<int, int>;
			for (const std::pair<coords, Tile>& tile : map)
			{
				tile.second.spriteObject->SetSprite(s.sprite);
			}
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Unloads the tile map, clearing all tiles.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Unload()
	{
		map.clear();
		tileSet.Clear();
		base = nullptr;
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the scale of each tile.
	 * \return
	 * Size of each tile.
	***************************************************************************/
	float TileMap::GetTileScale()
	{
		return scale;
	}

	/*!*************************************************************************
	 * \brief
	 * Calculates the offset for the translation of
	 * Assumes calculations from center of tile map.
	 * \param pos
	 * Position to offset to.
	 * \return
	 * Offset Vector
	***************************************************************************/
	AEVec2 TileMap::GetCentreOffset(AEVec2 pos)
	{
		float x_offset{ 0 };
		float y_offset{ 0 };
			
		x_offset = (scale * mapWidth) / 2 + pos.x;
		y_offset = (scale * mapHeight) / 2 + pos.y;

		return { x_offset, y_offset };
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the position of the tile map.
	 * \param pos
	 * Position to set.
	 * \return void
	***************************************************************************/
	void TileMap::SetPosition(AEVec2 pos)
	{
		if (base)
		{
			base->SetPos(pos);
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the position of the cell at the specified index/coordinates of the map
	 * \param x
	 * X coordinate.
	 * \param y
	 * Y coordinate.
	 * \return
	 * The world position of the cell at the index.
	***************************************************************************/
	AEVec2 TileMap::GetPositionAtIndex(int x, int y)
	{
		return (map.at({ x, y }).spriteObject->gameObject->transform.position);
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the tile at the specified index/coordinates of the map.
	 * \param x
	 * X coordinate.
	 * \param y
	 * Y coordinate.
	 * \return
	 * Reference to the tile object at the index
	***************************************************************************/
	Tile& TileMap::At(int x, int y)
	{
		return map.at({ x, y });
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the width of the map.
	 * \return
	 * Width of the map.
	***************************************************************************/
	int TileMap::GetMapWidth()
	{
		return mapWidth;
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the height of the map.
	 * \return
	 * Height of the map.
	***************************************************************************/
	int TileMap::GetMapHeight()
	{
		return mapHeight;
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the cells on the grid that corresponds to the tile map.
	 * Required for path finding to work correctly.
	 * \param grid
	 * Grid to set.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::SetGrid(Grid& grid)
	{
		//grid.SetAllOccupied();
		for (const auto& pair : map)
		{
			if (pair.second.collidable)
			{
				std::pair index = pair.first;
				grid.SetOccupied(index.first, index.second);
			}
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Inserts a tile at the specified coordinates.
	 * \param x
	 * X coordinate.
	 * \param y
	 * Y coordinate.
	 * \param type
	 * Type of the tile to insert.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Insert(int x, int y, TileType type)
	{

		AEVec2 offset = GetCentreOffset();
		AEVec2 pos = { x * scale - offset.x, y * scale - offset.y };
		TileSprite sprite = tileSet.GetTileSprite(type);

		if (map.find({ x, y }) != map.end())
		{
			Tile tile = map.at({ x, y });
			tile = ReplaceTile(tile, pos, sprite);
			map.erase({ x, y });
			map.insert({ {x++, y}, tile });
		}
		else
		{
			Tile tile = CreateNewTile(pos, sprite);
			map.insert({ {x++, y}, tile });
		}

		//temp hack
		for (auto collidableType : collidableList)
		{
			Tile& tile = map.at({ x - 1, y });
			if (type == collidableType)
			{
				tile.collidable = true;

				GameObject* gameObject = tile.spriteObject->gameObject;
				//gameObject->SetLayer(1);
				objMgr.AddComponent<RigidBody>(gameObject);
				gameObject->GetComponent<RigidBody>()->SetMass(0);
				objMgr.AddCollider(gameObject, true);
			}
			else {
				tile.collidable = false;
			}
		}

	}

	/*!*************************************************************************
	 * \brief
	 * Replaces the tile at the specified coordinates.
	 * \param x
	 * X coordinate.
	 * \param y
	 * Y coordinate.
	 * \param type
	 * Type of the tile to insert.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Replace(int x, int y, TileType type)
	{
		TileSprite sprite = tileSet.GetTileSprite(type);
		AEVec2 offset = GetCentreOffset();
		AEVec2 pos = { x * scale - offset.x, y * scale - offset.y };

		if (map.find({ x, y }) != map.end())
		{
			Tile tile = map.at({ x, y });
			tile = ReplaceTile(tile, pos, sprite);
			map.insert({ {x, y}, tile });
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Erases the tile at the specified coordinates.
	 * \param x
	 * X coordinate.
	 * \param y
	 * Y coordinate.
	 * \return
	 * void
	***************************************************************************/
	void TileMap::Erase(int x, int y)
	{
		std::pair<int, int> pos = { x,y };
		if (map.find(pos) != map.end())
		{
			GameObject* obj = map.at(pos).spriteObject->gameObject;
			BoxCollider* collider = obj->GetComponent<BoxCollider>();

			if (collider)
			{
				std::vector cellIndices = collider->GetCellIndexes();
				for (int index : cellIndices)
				{
					CollisionManager::ClearPartitionGridCell(index);
				}

				CollisionManager::RemoveCollider(collider);

			}
			objMgr.DestroyGameObject(obj);
			map.erase(pos);
		}
	}
	
	/*!*************************************************************************
	 * \brief
	 * Creates a new tile at the specified position.
	 * \param pos
	 * Position to place the tile.
	 * \param tileSprite
	 * Sprite of the tile.
	 * \param collidable
	 * True if the tile is collidable, false otherwise
	 * \return
	 * The Tile object that was created
	***************************************************************************/
	Tile TileMap::CreateNewTile(AEVec2 pos, TileSprite tileSprite, bool collidable)
	{
		GameObject* tileObj = objMgr.NewGameObject(base);
		tileObj->transform.scale = { scale / GRAPHICS::MESH_WIDTH, scale / GRAPHICS::MESH_HEIGHT };
		ImageComponent* spriteObj = objMgr.AddImage(tileObj, tileSprite.sprite);
		tileObj->SetPos(pos);

		//Set Collider
		if (collidable)
		{
			GameObject* gameObject = tileObj;
			objMgr.AddComponent<RigidBody>(gameObject);
			gameObject->GetComponent<RigidBody>()->SetMass(0);
			objMgr.AddCollider(gameObject, true);
		}

		Tile tile = { spriteObj };
		tile.type = tileSprite.type;

		return tile;
	}

	/*!*************************************************************************
	 * \brief
	 * Replaces the tile at the specified position.
	 * \param tile
	 * Tile to replace.
	 * \param pos
	 * Position to place the tile.
	 * \param tileSprite
	 * Sprite of the tile.
	 * \return
	 * The Tile object that was created
	***************************************************************************/
	//Reuse existing tile
	Tile TileMap::ReplaceTile(Tile tile, AEVec2 pos, TileSprite tileSprite)
	{
		GameObject* obj = tile.spriteObject->gameObject;
		tile.spriteObject->SetSprite(tileSprite.sprite);
		tile.type = tileSprite.type;
		obj->SetPos(pos);
		obj->SetActive(true);

		return tile;
	}
	
	/*!*************************************************************************
	 * \brief
	 * Sets the types of tiles that are collidable.
	 * \param typeList
	 * initializer list of the types to set
	 * \return
	 * void
	***************************************************************************/
	void TileMap::SetCollidableTypes(std::initializer_list<TileType> typeList)
	{
		collidableList = typeList;
	}

	/*!*************************************************************************
	 * \brief
	 * Sets whether the tile map should be visible.
	 * \param visible
	 * True if visible, false otherwise
	 * \return
	 * void
	***************************************************************************/
	void TileMap::SetVisible(bool vis)
	{
		for (const auto& pair : map)
		{
			pair.second.spriteObject->active = vis;
		}
	}

}
