#include "constants.h"

namespace StarBangBang
{
	namespace STRING_TAGS
	{
		const std::string&& NUMERALS_STRING				= "0123456789";
		const std::string&& TILEMAP_WIDTH_TAG			= "Width:";
		const std::string&& TILEMAP_HEIGHT_TAG			= "Height:";
		const std::string&& TILEMAP_SIZE_TAG			= "Tile Size:";
	}
	namespace RESOURCES
	{
		const std::string&& ROOT_PATH					= "../Resources/";
		const std::string&& LEVELS_PATH					= ROOT_PATH + "Levels/";
		const std::string&& MAINMENU_PATH				= "MainMenu/";
		const std::string&& PROTOTYPE_SPRITE_1_PATH		= ROOT_PATH + "PlanetTexture.png";
		const std::string&& PROTOTYPE_SPRITE_2_PATH		= ROOT_PATH + "boi.png";
		const std::string&& PROTOTYPE_SPRITE_GRASS_PATH = ROOT_PATH + "grass.png";
		const std::string&& PROTOTYPE_SPRITE_STONE_PATH = ROOT_PATH + "stone.png";
		const std::string&& SPRITE_PLAYER_PATH			= ROOT_PATH + "player.png";
						  
		const std::string&& STARTGAME_BUTTON_PATH		= ROOT_PATH + MAINMENU_PATH + "StartGameButton.png";
		const std::string&& SETTINGS_BUTTON_PATH		= ROOT_PATH + MAINMENU_PATH + "SettingsButton.png";
		const std::string&& CREDITS_BUTTON_PATH			= ROOT_PATH + MAINMENU_PATH + "CreditsButton.png";
		const std::string&& EXITGAME_BUTTON_PATH		= ROOT_PATH + MAINMENU_PATH + "ExitGameButton.png";
		const std::string&& LEVEL_TEST_PATH				= LEVELS_PATH + "test.txt";
	}
}