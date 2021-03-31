#pragma once
#include "GameObject.h"
#include "Sprite.h"

namespace StarBangBang
{
	class UIObject : public GameObject
	{
	public:
		UIObject();
		void Update();
		void Draw();
	private:
		Sprite s;
	};
}