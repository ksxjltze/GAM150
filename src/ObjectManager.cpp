#include "ObjectManager.h"
#include "TestObject.h"

TempTeam::GameObject* TempTeam::ObjectManager::LoadTestObject(GraphicsManager* graphicsManager, float width, float height, const char* spritePath)
{
	//temp
	TestObject* testObject = new TestObject();
	testObject->image = Image(graphicsManager->CreateMesh(width, height), graphicsManager->LoadTexture(spritePath), 1);
	gameObjectList.push_back(testObject);
	return testObject;
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
