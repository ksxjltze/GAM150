#include "TileMap.h"
#include "constants.h"
#include <fstream>
#include "GraphicsManager.h"

namespace StarBangBang
{

	TileMap::TileMap(ObjectManager& objM, GraphicsManager& gfxM) : scale{ 1.0f }, mapWidth{ 0 }, mapHeight{ 0 }, objMgr{ objM }, gfxMgr{ gfxM }, base{ nullptr }
	{
		
	}

	void TileMap::Init()
	{
		if (!base)
		{
			tileSet.Load(gfxMgr);
			base = objMgr.NewGameObject();
		}

	}

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

	void TileMap::Unload()
	{
		map.clear();
		tileSet.Clear();
		base = nullptr;
	}

	float TileMap::GetTileScale()
	{
		return scale;
	}

	AEVec2 TileMap::GetCentreOffset(AEVec2 pos)
	{
		float x_offset{ 0 };
		float y_offset{ 0 };
			
		x_offset = (scale * mapWidth) / 2 + pos.x;
		y_offset = (scale * mapHeight) / 2 + pos.y;

		return { x_offset, y_offset };
	}

	void TileMap::SetPosition(AEVec2 pos)
	{
		if (base)
		{
			base->SetPos(pos);
		}
	}

	int TileMap::GetMapWidth()
	{
		return mapWidth;
	}

	AEVec2 TileMap::GetPositionAtIndex(int x, int y)
	{
		return (map.at({ x, y }).spriteObject->gameObject->transform.position);
	}

	int TileMap::GetMapHeight()
	{
		return mapHeight;
	}

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

	Tile& TileMap::At(int x, int y)
	{
		return map.at({ x, y });
	}

	void TileMap::SetVisible(bool vis)
	{
		for (const auto& pair : map)
		{
			pair.second.spriteObject->active = vis;
		}
	}

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

	void TileMap::SetCollidableTypes(std::initializer_list<TileType> typeList)
	{
		collidableList = typeList;
	}

}
