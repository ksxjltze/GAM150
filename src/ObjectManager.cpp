#include "ObjectManager.h"
#include "Utils.h"
#include <typeinfo>

void StarBangBang::ObjectManager::AddComponent(GameObject* gameObject, _Component* component)
{
	componentList.push_back(component);
	gameObject->AddComponent(component);
}

void StarBangBang::ObjectManager::AddImage(GameObject* gameObject, Sprite sprite)
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
	std::vector<_Component*> components = gameObject->GetComponents();
	GameObject* newObject = new GameObject(*gameObject);
	for (_Component* component : components)
	{
		//_Component* newComponent = new _Component(newObject, component->id);
		_Component* newComponent = component->Clone(newObject, component);
		newObject->AddComponent(newComponent);

		//MAKE THIS BETTER
		if (typeid(*newComponent).name() == typeid(ImageComponent).name())
		{
			ImageComponent* newImageComponent = dynamic_cast<ImageComponent*>(newComponent);
			imageComponentList.push_back(newImageComponent);
		}
		else if (typeid(*newComponent).name() == typeid(Script).name())
		{
			scriptManager.AddScript(dynamic_cast<Script*>(newComponent));
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
	for (_Component* component : componentList)
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
	for (_Component* component : componentList)
	{
		component->Update();
	}
}
