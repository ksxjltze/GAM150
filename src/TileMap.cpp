#include "TileMap.h"
#include "constants.h"
#include <fstream>
#include "GraphicsManager.h"

namespace StarBangBang
{
	TileMap::TileMap(ObjectManager& objM, GraphicsManager& gfxM) : scale{ 1.0f }, mapWidth{ 0 }, mapHeight{ 0 }, objMgr{ objM }, gfxMgr{ gfxM }
	{
		
	}

	void TileMap::Init()
	{
		tileSet.Load(gfxMgr);
	}

	void TileMap::Generate(int width, int height, float tileSize)
	{
		//Default sprite
		TileSprite tileSprite = tileSet.GetTileSprite(TileType::STONE);

		float x_offset = tileSize * (width + 1) / 2;
		float y_offset = tileSize * (height + 1) / 2;

		mapWidth = width;
		mapHeight = height;
		scale = tileSize;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				std::pair<int, int> index = { x, y};
				AEVec2 pos = { x * scale - x_offset, y * scale - y_offset };

				Tile tile = CreateNewTile(pos, tileSprite);
				map.insert({ index, tile });
			}
		}
	}

	void StarBangBang::TileMap::Load(std::string path)
	{
		std::ifstream is;
		is.open(path);

		//Test
		scale = 50.0f;

		if (is.is_open())
		{
			//TEST
			mapWidth = 21;
			mapHeight = 21;

			//Centre TileMap
			float x_offset = (scale * mapWidth)  / 2;
			float y_offset = (scale * mapHeight) / 2;

			int y {0};

			while (!is.eof())
			{
				int x {0};
				std::string row;
				is >> row;

				for (auto ch : row)
				{
					int type = ch - '0';
					TileSprite sprite = tileSet.GetTileSprite(static_cast<TileType>(type));

					AEVec2 pos = { x * scale - x_offset, y * scale - y_offset};
					Tile tile = CreateNewTile(pos, sprite);
					map.insert({ {x++, y}, tile });
				}
				y++;

			}
			is.close();
		}
		else
		{
			fprintf(stderr, "TileMap: ERROR OPENING FILE\n");
		}
	}

	float TileMap::GetTileScale()
	{
		return scale;
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

		float x_offset = scale * (mapWidth + 1) / 2;
		float y_offset = scale * (mapHeight + 1) / 2;

		TileSprite sprite = tileSet.GetTileSprite(type);
		AEVec2 position = { x * scale - x_offset, y * scale - y_offset };

		Tile tile = CreateNewTile(position, sprite);

		std::pair<int, int> pos = { x, y };
		map.insert({ pos, tile });

	}

	void TileMap::Erase(int x, int y)
	{
		map.erase({ x, y });
	}
	
	Tile TileMap::CreateNewTile(AEVec2 pos, TileSprite tileSprite)
	{
		GameObject* tileObj = objMgr.NewGameObject();
		ImageComponent* spriteObj = objMgr.AddImage(tileObj, tileSprite.sprite);

		tileObj->SetPos(pos);
		Tile tile = { spriteObj };

		return tile;
	}

}
