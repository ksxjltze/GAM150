#pragma once
#include <string>

namespace StarBangBang
{
	enum SceneID {DEMO, EDITOR, SAMPLE, GAME, MAIN_MENU};

	namespace TILEMAP
	{
		static const int DEFAULT_WIDTH = 50;
		static const int DEFAULT_HEIGHT = 50;
		static const float DEFAULT_TILE_SIZE = 50.0f;
	}

	namespace GRAPHICS
	{
		static const float MESH_WIDTH = TILEMAP::DEFAULT_TILE_SIZE, MESH_HEIGHT = TILEMAP::DEFAULT_TILE_SIZE;
		static const float CAMERA_SCALE_FACTOR = 0.4f;
		static const float DEFAULT_ZOOM = 2.0f;
		static const float CAMERA_SCALE_MIN = 0.0f;
		static const float CAMERA_SCALE_MAX = 3.0f;

		static const float RESOLUTION_X = 1920.0f;
		static const float RESOLUTION_Y = 1080.0f;
		static const float TARGET_WINDOW_WIDTH = 800.0f;
		static const float TARGET_WINDOW_HEIGHT = 600.0f;
	}

	namespace CONSTANTS
	{
		static const float DEFAULT_OBJECT_SCALE = 1.0f;
		static const int COMPUTER_COUNT = 7;
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
		extern const std::string&& MAINMENU_PATH;
		extern const std::string&& CHARACTERS_PATH;
		extern const std::string&& FLOORTILES_PATH;
		extern const std::string&& INTERACTABLE_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_1_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_2_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_GRASS_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_STONE_PATH;
		extern const std::string&& SPRITE_PLAYER_PATH;

		namespace LEVELS
		{
			extern const std::string&& LEVEL_TEST_PATH;
			extern const std::string&& LEVEL_MAIN_MENU_TEST_PATH;
			extern const std::string&& COLLISION_TEST;
		}
								

		//main menu buttons sprites
		extern const std::string&& PLAY1_BUTTON_PATH;
		extern const std::string&& PLAY2_BUTTON_PATH;
		extern const std::string&& SETTING1_BUTTON_PATH;
		extern const std::string&& SETTING2_BUTTON_PATH;
		extern const std::string&& CREDIT1_BUTTON_PATH;
		extern const std::string&& CREDIT2_BUTTON_PATH;
		extern const std::string&& EXIT1_BUTTON_PATH;
		extern const std::string&& EXIT2_BUTTON_PATH;
		extern const std::string&& LOGO_PATH;

		//Character sprites
		extern const std::string&& CAPTAINSTEALTH_F1_PATH;
		extern const std::string&& CAPTAINSTEALTH_F2_PATH;
		extern const std::string&& CAPTAINSTEALTH_F3_PATH;

		extern const std::string&& CAPTAINSTEALTH_B1_PATH;
		extern const std::string&& CAPTAINSTEALTH_B2_PATH;
		extern const std::string&& CAPTAINSTEALTH_B3_PATH;

		extern const std::string&& CAPTAINSTEALTH_L1_PATH;
		extern const std::string&& CAPTAINSTEALTH_L2_PATH;
		extern const std::string&& CAPTAINSTEALTH_L3_PATH;

		extern const std::string&& CAPTAINSTEALTH_R1_PATH;
		extern const std::string&& CAPTAINSTEALTH_R2_PATH;
		extern const std::string&& CAPTAINSTEALTH_R3_PATH;

		extern const std::string&& PRISONER_F1_PATH;
		extern const std::string&& PRISONER_F2_PATH;
		extern const std::string&& PRISONER_F3_PATH;

		extern const std::string&& PRISONER_B1_PATH;
		extern const std::string&& PRISONER_B2_PATH;
		extern const std::string&& PRISONER_B3_PATH;

		extern const std::string&& PRISONER_L1_PATH;
		extern const std::string&& PRISONER_L2_PATH;
		extern const std::string&& PRISONER_L3_PATH;

		extern const std::string&& PRISONER_R1_PATH;
		extern const std::string&& PRISONER_R2_PATH;
		extern const std::string&& PRISONER_R3_PATH;

		extern const std::string&& SECURITYGUARD_F1_PATH;
		extern const std::string&& SECURITYGUARD_F2_PATH;
		extern const std::string&& SECURITYGUARD_F3_PATH;

		extern const std::string&& SECURITYGUARD_B1_PATH;
		extern const std::string&& SECURITYGUARD_B2_PATH;
		extern const std::string&& SECURITYGUARD_B3_PATH;

		extern const std::string&& SECURITYGUARD_L1_PATH;
		extern const std::string&& SECURITYGUARD_L2_PATH;
		extern const std::string&& SECURITYGUARD_L3_PATH;

		extern const std::string&& SECURITYGUARD_R1_PATH;
		extern const std::string&& SECURITYGUARD_R2_PATH;
		extern const std::string&& SECURITYGUARD_R3_PATH;

		//floortiles sprites
		extern const std::string&& BLACKBRICK_PATH;
		extern const std::string&& BLACKBRICK_UP_PATH;
		extern const std::string&& BLACKBRICK_DOWN_PATH;
		extern const std::string&& BLACKBRICK_LEFT_PATH;
		extern const std::string&& BLACKBRICK_RIGHT_PATH;


		extern const std::string&& REDBRICK_PATH;
		extern const std::string&& REDBRICK_UP_PATH;
		extern const std::string&& REDBRICK_DOWN_PATH;
		extern const std::string&& REDBRICK_LEFT_PATH;
		extern const std::string&& REDBRICK_RIGHT_PATH;

		extern const std::string&& OFFICEFLOOR_PATH;
		extern const std::string&& PRISONFLOOR_PATH;
		extern const std::string&& PRISONCELL_PATH;
		extern const std::string&& DOOR_PATH;

		//interactable objects
		extern const std::string&& CAMERA_PATH;
		extern const std::string&& BIN_PATH;
		extern const std::string&& BIN_RED_PATH;
		extern const std::string&& VENDING_LEFT_PATH;
		extern const std::string&& VENDING_LEFT_RED_PATH;
		extern const std::string&& VENDING_RIGHT_PATH;
		extern const std::string&& VENDING_RIGHT_RED_PATH;
		extern const std::string&& COMPUTER_PATH;



	}
}