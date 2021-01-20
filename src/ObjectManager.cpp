#include "ObjectManager.h"
#include "Utils.h"
#include <typeinfo>

void StarBangBang::ObjectManager::AddImageComponent(GameObject* gameObject, Sprite sprite)
{
	if (sprite.mesh != nullptr && sprite.texture != nullptr)
	{
		ImageComponent* image = new ImageComponent(gameObject, sprite.mesh, sprite.texture);
		imageComponentList.push_back(image);
		gameObject->AddComponent(image);
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

StarBangBang::GameObject* StarBangBang::ObjectManager::CloneGameObject(GameObject* gameObject)
{
	std::vector<Component*> components = gameObject->GetComponents();
	GameObject* newObject = new GameObject(*gameObject);
	for (Component* component : components)
	{
		//Component* newComponent = new Component(newObject, component->id);
		Component* newComponent = component->Clone(newObject, component);
		newObject->AddComponent(newComponent);

		//MAKE THIS BETTER
		if (newComponent->id == ImageComponent::id)
		{
			ImageComponent* newImageComponent = static_cast<ImageComponent*>(newComponent);
			imageComponentList.push_back(newImageComponent);
		}
		else
			componentList.push_back(newComponent);	

	}
	gameObjectList.push_back(newObject);
	return newObject;
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

	for (ImageComponent* imageComponent : imageComponentList)
	{
		delete imageComponent;
		imageComponent = nullptr;
	}

	componentList.clear();
	imageComponentList.clear();
}

void StarBangBang::ObjectManager::Draw()
{
	for (ImageComponent* image : imageComponentList)
	{
		image->Draw();
	}
}

void StarBangBang::ObjectManager::Update()
{
	for (Component* component : componentList)
	{
		component->Update();
	}
}
