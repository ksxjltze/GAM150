#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include <vector>

namespace TempTeam
{
	class ObjectManager
	{
	public:
		Image* ImageLoad(GraphicsManager &graphicsManager, float width, float height, const char* spritePath, float alpha);
		GameObject* InitTestObject(Image* image);
		void FreeObjects();
	private:
		std::vector<GameObject*> gameObjectList;
		std::vector<Image> imageList;
	};
}