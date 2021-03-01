#pragma once
#include <string>

namespace StarBangBang
{
	enum SCENE {DEMO, EDITOR, SAMPLE, GAME};
	namespace GRAPHICS
	{
		static const int MESH_WIDTH = 100, MESH_HEIGHT = 100;

	}

	namespace PLAYER
	{
		static const float PLAYER_SPEED = 300.0f;

	}
	namespace RESOURCES
	{
		extern const std::string&& ROOT_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_1_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_2_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_GRASS_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_STONE_PATH;
		extern const std::string&& SPRITE_PLAYER_PATH;
								 
		extern const std::string&& LEVEL_TEST_PATH;

	}
}