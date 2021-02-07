#pragma once
#include "ObjectManager.h"

namespace StarBangBang
{
	class MemoryManager
	{
	public:
		MemoryManager();
		MemoryManager(ObjectManager* objectManager, GraphicsManager* graphicsManager);
		void Load();
		void Free();
		void Unload();
	
	private:
		//Might wanna rethink how this is done
		ObjectManager* objectManager;
		GraphicsManager* graphicsManager;
	};
}