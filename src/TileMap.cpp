#include "TileMap.h"
#include "constants.h"
#include <fstream>
#include "GraphicsManager.h"

namespace StarBangBang
{
	TileMap::TileMap(ObjectManager& objM, GraphicsManager& gfxM) : scale{ 1.0f }, mapWidth{ 0 }, mapHeight{ 0 }, objMgr{ objM }, gfxMgr{ gfxM }
	{
		
	}

	void TileMap::Generate(int width, int height, float tileSize)
	{
		//Default sprite
		tileSet.Load(gfxMgr);
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
				std::pair<int, int> position = { x, y};

				GameObject* tileObj = objMgr.NewGameObject();
				tileObj->SetPos({x * tileSize - x_offset, y * tileSize - y_offset });
				
				ImageComponent* spriteObj = objMgr.AddImage(tileObj, tileSprite.sprite);
				Tile tile = { spriteObj };

				map.insert({ position, tile });
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

			tileSet.Load(gfxMgr);

			//Centre TileMap
			float x_offset = scale * mapWidth / 2;
			float y_offset = scale * mapHeight / 2;

			int y {0};

			while (!is.eof())
			{
				int x {0};
				std::string row;
				is >> row;

				for (auto ch : row)
				{
					int type = ch - '0';
					Sprite sprite = tileSet.GetTileSprite(static_cast<TileType>(type)).sprite;
					GameObject* tileObj = objMgr.NewGameObject();
					ImageComponent* spriteObj = objMgr.AddImage(tileObj, sprite);

					Tile tile{ spriteObj };
					tileObj->SetPos({ x * scale - x_offset, y * scale - y_offset});
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

}
