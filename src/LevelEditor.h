#pragma once
#include "State.h"
#include "GameStateManager.h"
#include "Sprite.h"
#include "Grid.h"
#include "CameraComponent.h"

namespace StarBangBang
{
	struct TileSprite
	{
		int id;
		std::string name;
		Sprite sprite;
	};

	struct Tile
	{
		TileSprite sprite;
		GameObject* gameObject;
	};

	class LevelEditor : public Scene
	{
	public:
		LevelEditor(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		void InsertTile(Node* n);
		void RemoveTile(Node* n);
		void SaveLevel();
		
		float tileWidth, tileHeight;
		int mapWidth, mapHeight;
		TileSprite selectedTile;

		std::map<std::string, TileSprite> palette;
		std::vector<std::vector<Tile>> tileObjects;

		GameObject* camera{ nullptr };
		Grid grid;
	};
}