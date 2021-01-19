#include "ObjectManager.h"
#include "Utils.h"

void StarBangBang::ObjectManager::AddImageComponent(GameObject* gameObject, Sprite sprite)
{
	if (sprite.mesh != nullptr && sprite.texture != nullptr)
	{
		ImageComponent image = ImageComponent(gameObject, sprite.mesh, sprite.texture);
		imageComponentList.push_back(image);
		gameObject->AddComponent(&imageComponentList.back());
	}
}

void StarBangBang::ObjectManager::AddChildGameObject(GameObject* child, GameObject* parent)
{
	child->parent = parent;
	AEVec2 newPos;
	AEVec2Sub(&newPos, &child->transform.position , &parent->transform.position);
	child->transform.position = newPos;
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
	gameObjectList.clear();
}

void StarBangBang::ObjectManager::FreeComponents()
{
	for (Component* component : componentList)
	{
		delete component;
		component = nullptr;
	}
	componentList.clear();
	imageComponentList.clear();
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
	for (Component* component : componentList)
	{
		component->Update();
	}
}
