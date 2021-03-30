#pragma once
#include "State.h"
#include "GameStateManager.h"
#include "Sprite.h"
#include "Grid.h"
#include "CameraComponent.h"
#include "SerializeTest.h"
#include "TileMap.h"
#include "DebugText.h"

namespace StarBangBang
{
	enum class BrushMode;

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
		void SaveLevel(const std::string& path);
		bool LoadLevel(const std::string& path);
		void CreateLevel(int width, int height, float tileSize, TileType type);
		void SetGrid();
		
		Sprite boi;
		std::string filepath;
		BrushMode brushMode;

		TileMap tileMap;
		TileType selectedType;
		Grid grid;

		GameObject* camera{ nullptr };
		GameObject* debugText{ nullptr };
		GameObject* tileOutline{ nullptr };
		ImageComponent* tileImg{ nullptr };
	};
}