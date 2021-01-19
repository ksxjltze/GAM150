#pragma once
#include "TileManager.h"
#include "State.h"

namespace StarBangBang
{
	class MapEditor : public State
	{
	public:
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		ObjectManager objectManager;
		GraphicsManager graphicsManager;
	};
}