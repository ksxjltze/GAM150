#include "TileMap.h"
#include "constants.h"
#include <fstream>
#include "GraphicsManager.h"

namespace StarBangBang
{
	TileMap::TileMap() : tileWidth{ 0 }, tileHeight{ 0 }, mapWidth{ 0 }, mapHeight{ 0 }
	{

	}

	void StarBangBang::TileMap::Load(std::string path, ObjectManager& objMgr, GraphicsManager& gfxMgr)
	{
		std::ifstream is;
		is.open(path);

		if (is.is_open())
		{
			int y {0};
			tileSet.Load(gfxMgr);

			while (!is.eof())
			{
				int x {0};
				std::string row;
				is >> row;

				//Test
				tileWidth = 50.0f;
				tileHeight = 50.0f;

				for (auto ch : row)
				{
					int type = ch - '0';
					Sprite sprite = tileSet.GetTileSprite(static_cast<TileType>(type)).sprite;
					GameObject* tileObj = objMgr.NewGameObject();
					ImageComponent* spriteObj = objMgr.AddImage(tileObj, sprite);

					Tile tile{ spriteObj };
					tileObj->SetPos({ x * tileWidth, y * tileHeight });
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

}
