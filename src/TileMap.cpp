#include "TileMap.h"
#include "constants.h"
#include <fstream>
#include "GraphicsManager.h"

namespace StarBangBang
{
	TileMap::TileMap() : scale{ 1.0f }, mapWidth{ 0 }, mapHeight{ 0 }
	{

	}

	void StarBangBang::TileMap::Load(std::string path, ObjectManager& objMgr, GraphicsManager& gfxMgr)
	{
		std::ifstream is;
		is.open(path);

		//Test
		scale = 50.0f;

		if (is.is_open())
		{
			//TEST
			mapWidth = 20;
			mapHeight = 20;

			int y {0};
			tileSet.Load(gfxMgr);

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
					tileObj->SetPos({ x * scale, y * scale });
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
