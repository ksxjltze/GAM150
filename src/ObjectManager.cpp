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
	if (gameObject)
	{
		if (sprite.mesh != nullptr && sprite.texture != nullptr)
		{
			ImageComponent* image = new ImageComponent(gameObject, sprite.mesh, sprite.texture);
			imageComponentList.push_back(image);
			gameObject->AddComponent(image);
		}

	}
}

void StarBangBang::ObjectManager::AddChildGameObject(GameObject* child, GameObject* parent)
{
	if (child && parent)
	{
		child->parent = parent;
		AEVec2 newPos;
		AEVec2Sub(&newPos, &child->transform.position , &parent->transform.position);
		child->transform.position = newPos;

	}
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
	if (gameObject)
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
			else
				componentList.push_back(newComponent);	

		}

		gameObjectList.push_back(newObject);
		return newObject;

	}
	return nullptr;
}

void StarBangBang::ObjectManager::DestroyGameObject(GameObject* gameObject)
{
	if (gameObject)
	{
		for (_Component* objComponent : gameObject->GetComponents())
		{
			for (auto image = imageComponentList.begin(); image != imageComponentList.end(); image++)
			{
				if (objComponent == *image)
				{
					delete *image;
					imageComponentList.erase(image);
					break;
				}
			}

			for (auto component = componentList.begin(); component != componentList.end(); component++)
			{
				if (objComponent == *component)
				{
					delete *component;
					componentList.erase(component);
					break;
				}
			}

		}

		delete gameObject;
	}
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

void StarBangBang::ObjectManager::Init()
{
	for (_Component* component : componentList)
	{
		component->Start();
	}
}

void StarBangBang::ObjectManager::Draw()
{
	for (ImageComponent* image : imageComponentList)
	{
		if (image->active)
		{
			image->Draw();
		}
	}
}

void StarBangBang::ObjectManager::Update()
{
	for (_Component* component : componentList)
	{
		if (component->active)
			component->Update();
	}
}
