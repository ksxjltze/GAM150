#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "TransformComponent.h"
#include "DragComponent.h"
#include <vector>

namespace TempTeam
{
	class ObjectManager
	{
	public:
		Image* ImageLoad(GraphicsManager &graphicsManager, float width, float height, const char* spritePath, float alpha);
		void AddImageComponent(GameObject* gameObject, GraphicsManager& graphicsManager, const char* spritePath);
		void AddTransformComponent(GameObject* gameObject);
		void AddDragComponent(GameObject* gameObject);
		GameObject* InitTestObject(Image* image);
		GameObject* NewGameObject();
		void FreeObjects();
		void UnloadImages();
		void Draw();
		void Update();
	private:
		std::vector<GameObject*> gameObjectList;
		std::vector<Image*> imageList;
		std::vector<ImageComponent> imageComponentList;
		std::vector<TransformComponent> transformComponentList;
		std::vector<DragComponent> dragComponentList;
	};
}