#pragma once
#include "State.h"
#include "GameStateManager.h"
#include "Sprite.h"
#include "Grid.h"
#include "CameraComponent.h"

namespace StarBangBang
{
	struct Tile
	{
		Sprite sprite;
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
		Sprite selectedTile;

		std::map<std::string, Sprite> palette;
		std::map<Node*, Tile> tileObjects;

		GameObject* camera{ nullptr };
		Grid grid;
	};
}