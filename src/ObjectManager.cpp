#include "ObjectManager.h"
#include "TestObject.h"

TempTeam::GameObject* TempTeam::ObjectManager::LoadTestObject(GraphicsManager* graphicsManager)
{
	//temp
	TestObject* testObject = new TestObject();
	testObject->image = Image(graphicsManager->CreateMesh(100, 100), graphicsManager->LoadTexture("../Resources/PlanetTexture.png"), 1);
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
