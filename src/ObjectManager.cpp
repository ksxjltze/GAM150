#include "ObjectManager.h"
#include "TestObject.h"
#include "Utils.h"

//Deprecated
StarBangBang::Image* StarBangBang::ObjectManager::ImageLoad(GraphicsManager& graphicsManager, float width, float height, const char* spritePath, float alpha)
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

void StarBangBang::ObjectManager::AddImageComponent(GameObject* gameObject, GraphicsManager& graphicsManager, const char* spritePath)
{
	AEGfxVertexList* mesh = graphicsManager.CreateMesh(gameObject->width, gameObject->height);
	AEGfxTexture* texture = graphicsManager.LoadTexture(spritePath);

	if (mesh != nullptr && texture != nullptr)
	{
		ImageComponent image = ImageComponent(gameObject, mesh, texture);
		imageComponentList.push_back(image);
	}
}

void StarBangBang::ObjectManager::AddTransformComponent(GameObject* gameObject)
{
	TransformComponent transform = TransformComponent(gameObject);
	transformComponentList.push_back(transform);
}

void StarBangBang::ObjectManager::AddDragComponent(GameObject* gameObject)
{
	DragComponent dragComponent(gameObject);
	dragComponentList.push_back(dragComponent);
}

//Deprecated
StarBangBang::GameObject* StarBangBang::ObjectManager::InitTestObject(Image* image)
{
	TestObject* object = new TestObject();
	object->image = image;
	object->Init();
	gameObjectList.push_back(object);
	return object;
}

StarBangBang::GameObject* StarBangBang::ObjectManager::NewGameObject()
{
	GameObject* gameObject = new GameObject();
	gameObjectList.push_back(gameObject);
	return gameObject;
}

StarBangBang::GameObject* StarBangBang::ObjectManager::NewGameObject(float width, float height)
{
	GameObject* gameObject = new GameObject();
	gameObject->width = width;
	gameObject->height = height;
	gameObjectList.push_back(gameObject);
	return gameObject;
}

void StarBangBang::ObjectManager::FreeObjects()
{
	for (GameObject* obj : gameObjectList)
	{
		if (obj)
		{
			delete obj;
		}
	}
}

void StarBangBang::ObjectManager::UnloadImages()
{
	for (Image* img : imageList)
	{
		if (img)
		{
			delete img;
		}
	}
}

void StarBangBang::ObjectManager::Draw()
{
	for (ImageComponent image : imageComponentList)
	{
		image.Draw();
	}
}

void StarBangBang::ObjectManager::Update()
{
	AEVec2 mousePos = GetMouseWorldPos();
	for (DragComponent &dragComponent : dragComponentList)
	{
		dragComponent.Update(mousePos);
	}
}
