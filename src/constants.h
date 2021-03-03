#pragma once
#include <string>

namespace StarBangBang
{
	enum SCENE {DEMO, EDITOR, SAMPLE, GAME, MAINMENU};
	namespace GRAPHICS
	{
		static const int MESH_WIDTH = 100, MESH_HEIGHT = 100;
		static const float CAMERA_SCALE_FACTOR = 0.2f;
		static const float CAMERA_SCALE_MIN = 0.0f;
		static const float CAMERA_SCALE_MAX = 3.0f;

	}

	namespace TILEMAP
	{
		static const float DEFAULT_WIDTH = 50.0f;
		static const float DEFAULT_HEIGHT = 50.0f;
		static const float DEFAULT_TILE_SIZE = 50.0f;
	}

	namespace PLAYER
	{
		static const float PLAYER_SPEED = 300.0f;

	}

	namespace STRING_TAGS
	{
		extern const std::string&& NUMERALS_STRING;
		extern const std::string&& TILEMAP_WIDTH_TAG;
		extern const std::string&& TILEMAP_HEIGHT_TAG;
		extern const std::string&& TILEMAP_SIZE_TAG;
	}

	namespace RESOURCES
	{
		extern const std::string&& ROOT_PATH;
		extern const std::string&& LEVELS_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_1_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_2_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_GRASS_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_STONE_PATH;
		extern const std::string&& SPRITE_PLAYER_PATH;
								 
		extern const std::string&& LEVEL_TEST_PATH;

		extern const std::string&& STARTGAME_BUTTON_PATH;
		extern const std::string&& SETTINGS_BUTTON_PATH;
		extern const std::string&& CREDITS_BUTTON_PATH;
		extern const std::string&& EXITGAME_BUTTON_PATH;
	}
}