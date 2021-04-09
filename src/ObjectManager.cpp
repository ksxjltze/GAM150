/******************************************************************************/
/*!
\title		Captain Stealth
\file		ObjectManager.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Object Manager class.
			Is responsible for the creation of game objects and adding components to them.
			Manages the lifetime of game objects and frees them when the scene is exited.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "ObjectManager.h"
#include "Utils.h"
#include <typeinfo>
#include <fstream>

namespace StarBangBang
{
	static const int NUM_MAX_LAYERS = 3;
}

StarBangBang::GameObject* StarBangBang::ObjectManager::Find(const std::string& name)
{
	for (auto gameObject : gameObjectList)
	{
		if (gameObject->name == name)
		{
			return gameObject;
		}
	}
	return nullptr;
}

StarBangBang::BoxCollider& StarBangBang::ObjectManager::AddCollider(GameObject* gameObject, bool isStatic)
{
	if (!gameObject->GetComponent<RigidBody>())
		AddComponent<RigidBody>(gameObject);

	BoxCollider* collider = CollisionManager::CreateBoxColliderInstance(gameObject, isStatic);
	assert(collider);

	componentList.push_back(collider);
	gameObject->AddComponent(collider);
	return *collider;
	
}

void StarBangBang::ObjectManager::AddComponent(GameObject* gameObject, GameComponent* component)
{
	componentList.push_back(component);
	gameObject->AddComponent(component);
}

StarBangBang::ImageComponent* StarBangBang::ObjectManager::AddImage(GameObject* gameObject, Sprite sprite)
{
	if (gameObject)
	{
		if (sprite.mesh != nullptr && sprite.texture != nullptr)
		{
			ImageComponent* image = new ImageComponent(gameObject, sprite.mesh, sprite.texture);
			componentList.push_back(image);
			gameObject->AddComponent(image);
			return image;
		}
		
	}
	return nullptr;
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

StarBangBang::GameObject* StarBangBang::ObjectManager::NewGameObject(GameObject* parent)
{
	GameObject* gameObject = NewGameObject();
	gameObject->parent = parent;
	return gameObject;
}

StarBangBang::GameObject* StarBangBang::ObjectManager::CloneGameObject(GameObject* gameObject)
{
	if (gameObject)
	{
		std::vector<GameComponent*> components = gameObject->GetComponents();
		GameObject* newObject = new GameObject(*gameObject);
		for (GameComponent* component : components)
		{
			//GameComponent* newComponent = new GameComponent(newObject, component->id);
			GameComponent* newComponent = component->Clone(newObject, component);
			newObject->AddComponent(newComponent);
			componentList.push_back(newComponent);	
		}

		gameObjectList.push_back(newObject);
		return newObject;

	}
	return nullptr;
}

void StarBangBang::ObjectManager::DestroyGameObject(GameObject* gameObject)
{
	//Could have pretty high overhead, maybe change this in the future
	if (gameObject)
	{
		//Delete components
		auto component_it = componentList.begin();
		while(component_it != componentList.end())
		{
			GameComponent*& component = *component_it;
			if (!component)
				continue;

			if (component->gameObject == gameObject)
			{
				delete component;
				component = nullptr;
				component_it = componentList.erase(component_it);
			}
			else
				component_it++;
		}

		//Delete game object
		for (auto gameObject_it = gameObjectList.begin(); gameObject_it != gameObjectList.end(); gameObject_it++)
		{
			if (*gameObject_it == gameObject)
			{
				gameObjectList.erase(gameObject_it);
				delete gameObject;
				return;
			}
			
		}
	}
}

void StarBangBang::ObjectManager::SaveGameObject(GameObject& gameObject)
{
	std::ofstream ofs;
	ofs.open("./Resources/test.bin", std::fstream::binary | std::ostream::trunc);
	if (ofs.is_open())
	{
		//Write Transform
		ofs.write(reinterpret_cast<const char*>(&gameObject.transform), sizeof(gameObject.transform));

		//Write Components
		for (GameComponent* c : (&gameObject)->GetComponents())
		{
			char test[64];
			memset(test, 0, 64);
			strcpy_s(test, 64, typeid(*c).name());

			ofs.write(reinterpret_cast<const char*>(&test), sizeof(test));
		}
		ofs.close();
	}
	else
		fprintf(stderr, "Object Manager: ERROR WRITING TO FILE");
}

StarBangBang::GameObject& StarBangBang::ObjectManager::ReadGameObject(const char* path)
{
	std::ifstream ifs;
	ifs.open(path);
	GameObject* gameObject = NewGameObject();

	if (ifs.is_open())
	{
		ifs.read(reinterpret_cast<char*>(&gameObject->transform), sizeof(Transform));

		Transform t = gameObject->transform;
		printf("Position: %f %f\n", t.position.x, t.position.y);
		printf("Rotation: %f\n", t.rotation);
		printf("Scale:	  %f %f\n", t.scale.x, t.scale.y);
		
		char type[64];
		memset(type, 0, 64);

		ifs.read(reinterpret_cast<char*>(&type), sizeof(type));
		printf("Component Type: %s", type);

		if (std::string(type) == std::string(typeid(ImageComponent).name()))
		{
			printf("COMPONENT MATCH\n");
		}

		ifs.close();
	}
	else
		fprintf(stderr, "Object Manager: ERROR READING FILE");

	return *gameObject;
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
	for (GameComponent* component : componentList)
	{
		delete component;
	}

	componentList.clear();
}

void StarBangBang::ObjectManager::Init()
{
	layerMap.clear();
	for (int i = 0; i < NUM_MAX_LAYERS; ++i)
	{
		layerMap.insert({ i, std::vector<GameComponent**>() });
	}

	for (GameComponent* component : componentList)
	{
		component->Start();
	}

	for (GameComponent*& component : componentList)
	{
		layerMap.at(component->gameObject->layer).push_back(&component);
	}

}

void StarBangBang::ObjectManager::Draw()
{
	for (int i = 0; i < NUM_MAX_LAYERS; ++i)
	{
		for (GameComponent** component : layerMap.at(i))
		{
			if (*component)
				(*component)->Draw();
		}

	}

	//for (GameComponent* component : componentList)
	//{
	//	if (component->gameObject->visible && component->active)
	//		component->Draw();
	//}
}

void StarBangBang::ObjectManager::Update()
{
	for (GameComponent* component : componentList)
	{
		if (component->gameObject->parent)
			component->gameObject->active = component->gameObject->parent->active;

		if (component->active && component->gameObject->active)
			component->Update();
	}
}

void StarBangBang::ObjectManager::LateUpdate()
{
	for (GameComponent* component : componentList)
	{
		if (component->active)
			component->LateUpdate();
	}
}
