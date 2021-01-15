#include "ObjectManager.h"
#include "TestObject.h"

TempTeam::Image* TempTeam::ObjectManager::ImageLoad(GraphicsManager& graphicsManager, float width, float height, const char* spritePath, float alpha)
{
	AEGfxVertexList* mesh = graphicsManager.CreateMesh(width, height);
	AEGfxTexture* texture = graphicsManager.LoadTexture(spritePath);

	if (mesh != nullptr && texture != nullptr)
	{
		Image image = Image(mesh, texture, alpha);
		imageList.push_back(image);
		return &imageList.back();
	}

	return nullptr;
}

TempTeam::GameObject* TempTeam::ObjectManager::InitTestObject(Image* image)
{
	TestObject* object = new TestObject();
	object->image = image;
	object->Init();
	gameObjectList.push_back(object);
	return object;
}

void TempTeam::ObjectManager::FreeObjects()
{
	for (GameObject* obj : gameObjectList)
	{
		if (obj)
		{
			delete obj;
		}
	}
}
