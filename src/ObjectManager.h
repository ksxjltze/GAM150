#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include <vector>

namespace TempTeam
{
	class ObjectManager
	{
	public:
		GameObject* LoadTestObject(GraphicsManager* graphicsManager);
		void FreeObjects();
	private:
		std::vector<GameObject*> gameObjectList;
	};
}