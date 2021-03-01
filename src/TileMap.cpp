#include "TileMap.h"
#include "constants.h"
#include <fstream>
#include "GraphicsManager.h"

namespace StarBangBang
{
	struct Tile
	{
		ImageComponent* spriteObject;
	};

	void StarBangBang::TileMap::Load(std::string path, ObjectManager& objMgr, GraphicsManager& gfxMgr)
	{
		std::ifstream is;
		is.open(path);

		if (is.is_open())
		{
			int y {0};

			while (!is.eof())
			{
				int x {0};
				std::string row;
				is >> row;

				//Test
				Sprite sprite = gfxMgr.CreateSprite(RESOURCES::PROTOTYPE_SPRITE_GRASS_PATH);

				for (auto ch : row)
				{
					GameObject* tileObj = objMgr.NewGameObject();
					ImageComponent* spriteObj = objMgr.AddImage(tileObj, sprite);

					Tile tile{ spriteObj };
					map.insert({ {x++, y}, tile });
				}
				y++;

			}
			is.close();
		}
	}

}
