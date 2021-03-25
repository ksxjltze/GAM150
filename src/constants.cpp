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
		//Folder paths
		const std::string&& ROOT_PATH					= "./Resources/";
		const std::string&& INTERACTABLE_PATH			= ROOT_PATH + "InteractableObj/";
		const std::string&& LEVELS_PATH					= ROOT_PATH + "Levels/";
		const std::string&& MAINMENU_PATH				= ROOT_PATH + "MainMenu/";
		const std::string&& CHARACTERS_PATH				= ROOT_PATH + "Characters/";
		const std::string&& FLOORTILES_PATH				= ROOT_PATH + "FloorTiles/";
		const std::string&& MISC_PATH					= ROOT_PATH + "Misc/";

		namespace LEVELS
		{
			const std::string&& LEVEL_TEST_PATH = LEVELS_PATH + "test.txt";
			const std::string&& LEVEL_MAIN_MENU_TEST_PATH = LEVELS_PATH + "title.csv";
			const std::string&& COLLISION_TEST = LEVELS_PATH + "collision.csv";
		}
		
		//Images path
		const std::string&& PROTOTYPE_SPRITE_1_PATH = ROOT_PATH + "PlanetTexture.png";
		const std::string&& PROTOTYPE_SPRITE_2_PATH = ROOT_PATH + "boi.png";
		const std::string&& PROTOTYPE_SPRITE_GRASS_PATH = ROOT_PATH + "grass.png";
		const std::string&& PROTOTYPE_SPRITE_STONE_PATH = ROOT_PATH + "stone.png";
		const std::string&& SPRITE_PLAYER_PATH = ROOT_PATH + "player.png";

		//main menu buttons sprites
		const std::string&& PLAY1_BUTTON_PATH			= MAINMENU_PATH + "Play1.png";
		const std::string&& PLAY2_BUTTON_PATH			= MAINMENU_PATH + "Play2.png";
		const std::string&& SETTING1_BUTTON_PATH		= MAINMENU_PATH + "Setting1.png";
		const std::string&& SETTING2_BUTTON_PATH		= MAINMENU_PATH + "Setting2.png";
		const std::string&& CREDIT1_BUTTON_PATH			= MAINMENU_PATH + "Credit1.png";
		const std::string&& CREDIT2_BUTTON_PATH			= MAINMENU_PATH + "Credit2.png";
		const std::string&& EXIT1_BUTTON_PATH			= MAINMENU_PATH + "Exit1.png";
		const std::string&& EXIT2_BUTTON_PATH			= MAINMENU_PATH + "Exit2.png";
		const std::string&& LOGO_PATH					= MAINMENU_PATH + "Logo.png";

		//Character sprites
		const std::string&& CAPTAINSTEALTH_F1_PATH			= CHARACTERS_PATH + "CaptainStealthForward1.png";
		const std::string&& CAPTAINSTEALTH_F2_PATH			= CHARACTERS_PATH + "CaptainStealthForward2.png";
		const std::string&& CAPTAINSTEALTH_F3_PATH			= CHARACTERS_PATH + "CaptainStealthForward3.png";

		const std::string&& CAPTAINSTEALTH_B1_PATH			= CHARACTERS_PATH + "CaptainStealthBack1.png";
		const std::string&& CAPTAINSTEALTH_B2_PATH			= CHARACTERS_PATH + "CaptainStealthBack2.png";
		const std::string&& CAPTAINSTEALTH_B3_PATH			= CHARACTERS_PATH + "CaptainStealthBack3.png";

		const std::string&& CAPTAINSTEALTH_L1_PATH			= CHARACTERS_PATH + "CaptainStealthLeft1.png";
		const std::string&& CAPTAINSTEALTH_L2_PATH			= CHARACTERS_PATH + "CaptainStealthLeft2.png";
		const std::string&& CAPTAINSTEALTH_L3_PATH			= CHARACTERS_PATH + "CaptainStealthLeft3.png";

		const std::string&& CAPTAINSTEALTH_R1_PATH			= CHARACTERS_PATH + "CaptainStealthRight1.png";
		const std::string&& CAPTAINSTEALTH_R2_PATH			= CHARACTERS_PATH + "CaptainStealthRight2.png";
		const std::string&& CAPTAINSTEALTH_R3_PATH			= CHARACTERS_PATH + "CaptainStealthRight3.png";

		const std::string&& PRISONER_F1_PATH				= CHARACTERS_PATH + "PrisonerForward1.png";
		const std::string&& PRISONER_F2_PATH				= CHARACTERS_PATH + "PrisonerForward2.png";
		const std::string&& PRISONER_F3_PATH				= CHARACTERS_PATH + "PrisonerForward3.png";

		const std::string&& PRISONER_B1_PATH				= CHARACTERS_PATH + "PrisonerBack1.png";
		const std::string&& PRISONER_B2_PATH				= CHARACTERS_PATH + "PrisonerBack2.png";
		const std::string&& PRISONER_B3_PATH				= CHARACTERS_PATH + "PrisonerBack3.png";

		const std::string&& PRISONER_L1_PATH				= CHARACTERS_PATH + "PrisonerLeft1.png";
		const std::string&& PRISONER_L2_PATH				= CHARACTERS_PATH + "PrisonerLeft2.png";
		const std::string&& PRISONER_L3_PATH				= CHARACTERS_PATH + "PrisonerLeft3.png";

		const std::string&& PRISONER_R1_PATH				= CHARACTERS_PATH + "PrisonerRight1.png";
		const std::string&& PRISONER_R2_PATH				= CHARACTERS_PATH + "PrisonerRight2.png";
		const std::string&& PRISONER_R3_PATH				= CHARACTERS_PATH + "PrisonerRight3.png";

		const std::string&& SECURITYGUARD_F1_PATH			= CHARACTERS_PATH + "SecurityGuardForward1.png";
		const std::string&& SECURITYGUARD_F2_PATH			= CHARACTERS_PATH + "SecurityGuardForward2.png";
		const std::string&& SECURITYGUARD_F3_PATH			= CHARACTERS_PATH + "SecurityGuardForward3.png";

		const std::string&& SECURITYGUARD_B1_PATH			= CHARACTERS_PATH + "SecurityGuardBack1.png";
		const std::string&& SECURITYGUARD_B2_PATH			= CHARACTERS_PATH + "SecurityGuardBack2.png";
		const std::string&& SECURITYGUARD_B3_PATH			= CHARACTERS_PATH + "SecurityGuardBack3.png";

		const std::string&& SECURITYGUARD_L1_PATH			= CHARACTERS_PATH + "SecurityGuardLeft1.png";
		const std::string&& SECURITYGUARD_L2_PATH			= CHARACTERS_PATH + "SecurityGuardLeft2.png";
		const std::string&& SECURITYGUARD_L3_PATH			= CHARACTERS_PATH + "SecurityGuardLeft3.png";

		const std::string&& SECURITYGUARD_R1_PATH			= CHARACTERS_PATH + "SecurityGuardRight1.png";
		const std::string&& SECURITYGUARD_R2_PATH			= CHARACTERS_PATH + "SecurityGuardRight2.png";
		const std::string&& SECURITYGUARD_R3_PATH			= CHARACTERS_PATH + "SecurityGuardRight3.png";

		//floortiles sprites
		const std::string&& BLACKBRICK_PATH					= FLOORTILES_PATH + "BlackBrick.png";
		const std::string&& BLACKBRICK_UP_PATH				= FLOORTILES_PATH + "BlackBrickUp.png";
		const std::string&& BLACKBRICK_DOWN_PATH			= FLOORTILES_PATH + "BlackBrickDown.png";
		const std::string&& BLACKBRICK_LEFT_PATH			= FLOORTILES_PATH + "BlackBrickLeft.png";
		const std::string&& BLACKBRICK_RIGHT_PATH			= FLOORTILES_PATH + "BlackBrickRight.png";


		const std::string&& REDBRICK_PATH					= FLOORTILES_PATH + "RedBrick.png";
		const std::string&& REDBRICK_UP_PATH				= FLOORTILES_PATH + "RedBrickUp.png";
		const std::string&& REDBRICK_DOWN_PATH				= FLOORTILES_PATH + "RedBrickDown.png";
		const std::string&& REDBRICK_LEFT_PATH				= FLOORTILES_PATH + "RedBrickLeft.png";
		const std::string&& REDBRICK_RIGHT_PATH				= FLOORTILES_PATH + "RedBrickRight.png";
		
		const std::string&& OFFICEFLOOR_PATH				= FLOORTILES_PATH + "OfficeFloor.png";
		const std::string&& PRISONFLOOR_PATH				= FLOORTILES_PATH + "PrisonFloor.png";
		const std::string&& PRISONCELL_PATH					= FLOORTILES_PATH + "prisoncell.png";
		const std::string&& DOOR_PATH						= FLOORTILES_PATH + "Door.png";

		//interactable objects
		const std::string&& CAMERA_PATH						= INTERACTABLE_PATH + "CameraUp.png";
		const std::string&&	BIN_PATH						= INTERACTABLE_PATH + "bin.png";
		const std::string&& BIN_RED_PATH					= INTERACTABLE_PATH + "bin1.png";
		const std::string&& VENDING_LEFT_PATH				= INTERACTABLE_PATH + "VendingMachineLeft.png";
		const std::string&& VENDING_LEFT_RED_PATH			= INTERACTABLE_PATH + "VendingMachineLeft1.png";
		const std::string&& VENDING_RIGHT_PATH				= INTERACTABLE_PATH + "VendingMachineRight.png";
		const std::string&& VENDING_RIGHT_RED_PATH			= INTERACTABLE_PATH + "VendingMachineRight1.png";
		const std::string&& COMPUTER_PATH					= INTERACTABLE_PATH + "Computer.png";
		const  std::string&& KEY_PATH						= INTERACTABLE_PATH + "keys.png";

		//misc objects
		const std::string&& INDICATOR_PATH					= MISC_PATH + "Indicator.png";

	}
}