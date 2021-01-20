#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "DragComponent.h"
#include "Sprite.h"
#include <vector>

namespace StarBangBang
{
	class ObjectManager
	{
	public:
		template <class T>
		void AddComponent(GameObject* gameObject)
		{
			T* component = new T(gameObject);
			componentList.push_back(component);
			gameObject->AddComponent(component);
		}

		void AddImageComponent(GameObject* gameObject, Sprite sprite);
		void AddChildGameObject(GameObject* child, GameObject* parent);
		//GameObject* InitTestObject(Image* image);
		GameObject* NewGameObject();
		GameObject* NewGameObject(float width, float height);
		GameObject* CloneGameObject(GameObject* gameObject);
		void FreeObjects();
		void FreeComponents();
		void Draw();
		void Update();
	private:
		std::vector<GameObject*> gameObjectList;
		std::vector<ImageComponent*> imageComponentList;
		std::vector<Component*> componentList;
	};
}