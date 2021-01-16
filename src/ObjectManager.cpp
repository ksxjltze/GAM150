#include "ObjectManager.h"
#include "TestObject.h"

TempTeam::Image* TempTeam::ObjectManager::ImageLoad(GraphicsManager& graphicsManager, float width, float height, const char* spritePath, float alpha)
{
	AEGfxVertexList* mesh = graphicsManager.CreateMesh(width, height);
	AEGfxTexture* texture = graphicsManager.LoadTexture(spritePath);

	if (mesh != nullptr && texture != nullptr)
	{
		Image* image = new Image(mesh, texture, alpha);
		imageList.push_back(image);
		return image;
	}

	return nullptr;
}

void TempTeam::ObjectManager::AddImageComponent(GameObject* gameObject, GraphicsManager& graphicsManager, float width, float height, const char* spritePath)
{
	AEGfxVertexList* mesh = graphicsManager.CreateMesh(width, height);
	AEGfxTexture* texture = graphicsManager.LoadTexture(spritePath);

	if (mesh != nullptr && texture != nullptr)
	{
		ImageComponent image = ImageComponent(gameObject, mesh, texture);
		imageComponentList.push_back(image);
	}
}

void TempTeam::ObjectManager::AddTransformComponent(GameObject* gameObject)
{
	TransformComponent transform = TransformComponent(gameObject);
	transformComponentList.push_back(transform);
}

TempTeam::GameObject* TempTeam::ObjectManager::InitTestObject(Image* image)
{
	TestObject* object = new TestObject();
	object->image = image;
	object->Init();
	gameObjectList.push_back(object);
	return object;
}

TempTeam::GameObject* TempTeam::ObjectManager::NewGameObject()
{
	GameObject* gameObject = new GameObject();
	gameObjectList.push_back(gameObject);
	return gameObject;
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

void TempTeam::ObjectManager::UnloadImages()
{
	for (Image* img : imageList)
	{
		if (img)
		{
			delete img;
		}
	}
}

void TempTeam::ObjectManager::Draw()
{
	for (ImageComponent image : imageComponentList)
	{
		image.Draw();
	}
}
