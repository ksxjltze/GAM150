#pragma once
#include "ObjectManager.h"

namespace StarBangBang
{
	class MemoryManager
	{
	public:
		MemoryManager(ObjectManager* objectManager, GraphicsManager* graphicsManager);
		void Load();
		void Free();
		void Unload();
	
	private:
		ObjectManager* objectManager;
		GraphicsManager* graphicsManager;
	};
}