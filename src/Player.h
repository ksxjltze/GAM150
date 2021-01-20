#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class Player
	{
	public:
		void Load(GraphicsManager& gfxManager);
		void Start(ObjectManager& objManager);
		void Update();
	private:
		GameObject* gameObject;
		Sprite image;
	};
}

