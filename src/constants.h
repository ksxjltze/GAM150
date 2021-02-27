#pragma once

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
		static const char* PROTOTYPE_SPRITE_1_PATH = "../Resources/PlanetTexture.png";
		static const char* PROTOTYPE_SPRITE_2_PATH = "../Resources/boi.png";
		static const char* PROTOTYPE_SPRITE_GRASS_PATH = "../Resources/grass.png";
		static const char* PROTOTYPE_SPRITE_STONE_PATH = "../Resources/stone.png";
		static const char* SPRITE_PLAYER_PATH = "../Resources/player.png";

	}
}