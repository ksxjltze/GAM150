#pragma once
#include <string>
#include "AEEngine.h"

namespace StarBangBang
{
	enum SceneID {GAME, EDITOR, SAMPLE, TUTORIAL, MAIN_MENU, GAME_OVER, CREDITS};
	enum LAYER { BACKGROUND, FOREGROUND, UI};
	enum class ChannelGroupId { SFX, BGM, ALL };
	enum class direction { idle = 0, left, right };
	enum class current_char { fei_ge, prisoner };

	namespace SFX
	{
		extern const std::string&& DETECTED;
		extern const std::string&& BUTTON_CLICK;
		extern const std::string&& KEY_PICKUP;
		extern const std::string&& DOOR_OPEN;
		extern const std::string&& VENT_CLOSE;
		extern const std::string&& VENT_OPEN;
		extern const std::string&& FOOTSTEPS;
	}

	namespace BGM
	{
		extern const std::string&& MENU;
		extern const std::string&& GAME;
		extern const std::string&& GAMEOVER;
	}

	namespace KEYBIND
	{
		static const int MOVEMENT_UP = AEVK_UP;
		static const int MOVEMENT_DOWN = AEVK_DOWN;
		static const int MOVEMENT_LEFT = AEVK_LEFT;
		static const int MOVEMENT_RIGHT = AEVK_RIGHT;

		static const int MOVEMENT_UP_ALT = AEVK_W;
		static const int MOVEMENT_DOWN_ALT = AEVK_S;
		static const int MOVEMENT_LEFT_ALT = AEVK_A;
		static const int MOVEMENT_RIGHT_ALT = AEVK_D;
	}

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
		static const int COMPUTER_COUNT = 3;
	}

	namespace PLAYER
	{
		static const float PLAYER_SPEED = 300.0f;
	}

	namespace GUARD
	{
		static const float GUARD_FOV = 50.f;
		static const float CAM_FOV = 50.f;

		static const float GUARD_VIEW_DIST = 250.f;
		static const float CAM_VIEW_DIST = 300.f;

		static const float GUARD_SPEED = 20.f;
		static const float CAM_ROT_SPEED = 25.f;
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
		extern const std::string&& MISC_PATH;
		extern const std::string&& INTERACTABLE_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_1_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_2_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_GRASS_PATH;
		extern const std::string&& PROTOTYPE_SPRITE_STONE_PATH;
		extern const std::string&& SPRITE_PLAYER_PATH;
		extern const std::string&& CREDITS_PATH;
		extern const std::string&& EYE_SPRITE_PATH;

		namespace SFX
		{
			extern const std::string&& SFX_KEY_PICKUP_PATH;
			extern const std::string&& SFX_BUTTON_CLICK_PATH;
			extern const std::string&& SFX_DETECTED_PATH;
			extern const std::string&& SFX_DOOR_OPEN_PATH;
			extern const std::string&& SFX_VENT_OPEN_PATH;
			extern const std::string&& SFX_VENT_CLOSE_PATH;
			extern const std::string&& SFX_WALK_FOOTSTEPS_PATH;
		}

		namespace BGM
		{
			extern const std::string&& BGM_MENU_PATH;
			extern const std::string&& BGM_GAME_PATH;
			extern const std::string&& BGM_GAMEOVER_PATH;
		}

		namespace LEVELS
		{
			extern const std::string&& LEVEL_TEST_PATH;
			extern const std::string&& LEVEL_MAIN_MENU_TEST_PATH;
			extern const std::string&& COLLISION_TEST;
			extern const std::string&& LEVEL_TUTORIAL;
		}
								

		//main menu buttons sprites
		extern const std::string&& PLAY1_BUTTON_PATH;
		extern const std::string&& PLAY2_BUTTON_PATH;
		extern const std::string&& RESUME_BUTTON_PATH;
		extern const std::string&& SETTING1_BUTTON_PATH;
		extern const std::string&& SETTING2_BUTTON_PATH;
		extern const std::string&& CREDIT1_BUTTON_PATH;
		extern const std::string&& CREDIT2_BUTTON_PATH;
		extern const std::string&& EXIT1_BUTTON_PATH;
		extern const std::string&& EXIT2_BUTTON_PATH;
		extern const std::string&& RESTART_BUTTON_PATH;
		extern const std::string&& LOGO_PATH;
		extern const std::string&& BACK_BUTTON_PATH;
		extern const std::string&& TUTORIAL_BUTTON_PATH;
		extern const std::string&& FULLSCREEN_BUTTON_PATH;
		extern const std::string&& MUTE_BUTTON_PATH;

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
		extern const std::string&& KEY_PATH;
		extern const std::string&& VENT_CLOSE_PATH;
		extern const std::string&& VENT_OPEN_PATH;

		//misc objects
		extern const std::string&& INDICATOR_PATH;
		extern const std::string&& TABBUTTON_PATH;
		extern const std::string&& ARROWKEYS_PATH;





	}
}