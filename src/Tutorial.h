#pragma once
#include "State.h"
#include "TileMap.h"

namespace StarBangBang
{
	class Tutorial : public Scene
	{
	public:
		Tutorial(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();

	private:
		void NewTextObject(AEVec2 position, const std::string& s, float scale = 1.0f);
		GameObject* cameraObject{ nullptr };
		GameObject* end{ nullptr };
		GameObject* player{ nullptr };
		void MainMenu();

		Sprite tutorialSprite;
		Sprite movementSprite;
		Sprite tabSprite;
		Sprite ventSprite;
		Sprite distractSprite;
		Sprite distractSprite2;
		Sprite backSprite;
		TileMap tilemap;
	};

}