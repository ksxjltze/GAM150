#pragma once
#include "State.h"
#include "GameStateManager.h"
#include "Sprite.h"
#include "Grid.h"
#include "CameraComponent.h"
#include "SerializeTest.h"

namespace StarBangBang
{
	struct TileSprite_Old
	{
		int id = -1;
		std::string name;
		Sprite sprite;
	};

	struct Tile_Old
	{
		TileSprite_Old sprite;
		GameObject* gameObject { nullptr };
	};

	class LevelEditor : public Scene
	{
	public:
		LevelEditor(int id, GameStateManager& manager);
		~LevelEditor();

		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		void InsertTile(A_Node* n);
		void RemoveTile(A_Node* n);
		void SaveLevel();
		void LoadLevel();
		void CreateLevel();
		
		float tileWidth, tileHeight;
		int mapWidth, mapHeight;
		TileSprite_Old selectedTile;
		Sprite boi;

		std::map<int, TileSprite_Old> palette;
		std::vector<std::vector<Tile_Old>> tileObjects;

		GameObject* camera{ nullptr };
		Grid grid;

		SerializeTest& serializeTestObj;
	};
}