#include "TileMap.h"
#include "constants.h"
#include <fstream>
#include "GraphicsManager.h"

#include "PrimaryMovementController.h"

namespace StarBangBang
{
	TileMap::TileMap(ObjectManager& objM, GraphicsManager& gfxM) : scale{ 1.0f }, mapWidth{ 0 }, mapHeight{ 0 }, objMgr{ objM }, gfxMgr{ gfxM }
	{
		
	}

	void TileMap::Init()
	{
		tileSet.Load(gfxMgr);
		base = objMgr.NewGameObject();
	}

	void TileMap::Generate(int width, int height, float tileSize)
	{
		//Default sprite
		TileSprite tileSprite = tileSet.GetTileSprite(TileType::STONE);

		AEVec2 offset = GetCentreOffset();

		mapWidth = width;
		mapHeight = height;
		scale = tileSize;

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
		std::ifstream is;
		is.open(path);

		if (is.is_open())
		{
			//Clear map
			if (!map.empty())
			{
				using coords = std::pair<int, int>;
				for (const std::pair<coords, Tile>& tile : map)
				{
					GameObject* obj = tile.second.spriteObject->gameObject;
					objMgr.DestroyGameObject(obj);
				}
				map.clear();
			}

			std::string widthStr;
			std::string heightStr;
			std::string sizeStr;

			is >> widthStr;

			if(widthStr.find(STRING_TAGS::TILEMAP_WIDTH_TAG) == widthStr.npos)
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

				for (auto ch : row)
				{
					//Improve later to accomodate for > 10
					if (ch != ',')
					{
						TileType type = static_cast<TileType>(ch - '0');

						if (type != TileType::NONE)
						{
							TileSprite sprite = tileSet.GetTileSprite(type);

							AEVec2 pos = { x * scale - offset.x, y * scale - offset.y};
							Tile tile = CreateNewTile(pos, sprite);
							map.insert({ {x++, y}, tile });

						}
						else
							++x;

					}
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

	int TileMap::GetMapHeight()
	{
		return mapHeight;
	}

	void TileMap::Insert(int x, int y, TileType type)
	{
		if (map.find({ x,y }) != map.end())
		{
			objMgr.DestroyGameObject(map.at({ x, y }).spriteObject->gameObject);
			Erase(x, y);
		}

		float x_offset = (scale * mapWidth) / 2;
		float y_offset = (scale * mapHeight) / 2;

		TileSprite sprite = tileSet.GetTileSprite(type);
		AEVec2 position = { x * scale - x_offset, y * scale - y_offset };

		Tile tile = CreateNewTile(position, sprite);

		std::pair<int, int> pos = { x, y };
		map.insert({ pos, tile });

	}

	void TileMap::Erase(int x, int y)
	{
		std::pair<int, int> pos = { x,y };
		if (map.find(pos) != map.end())
		{
			GameObject* obj = map.at(pos).spriteObject->gameObject;
			objMgr.DestroyGameObject(obj);
			map.erase(pos);
		}
	}
	
	Tile TileMap::CreateNewTile(AEVec2 pos, TileSprite tileSprite)
	{
		GameObject* tileObj = objMgr.NewGameObject(base);
		tileObj->transform.scale = { scale / GRAPHICS::MESH_WIDTH, scale / GRAPHICS::MESH_HEIGHT };
		ImageComponent* spriteObj = objMgr.AddImage(tileObj, tileSprite.sprite);

		tileObj->SetPos(pos);
		Tile tile = { spriteObj };
		tile.type = tileSprite.type;

		return tile;
	}

}
