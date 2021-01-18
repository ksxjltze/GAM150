#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "TransformComponent.h"
#include "DragComponent.h"
#include <vector>

namespace StarBangBang
{
	class ObjectManager
	{
	public:
		Image* ImageLoad(GraphicsManager &graphicsManager, float width, float height, const char* spritePath, float alpha);
		void AddImageComponent(GameObject* gameObject, GraphicsManager& graphicsManager, const char* spritePath);
		void AddImageComponent(GameObject* gameObject, AEGfxTexture* texture, AEGfxVertexList* mesh);
		void AddTransformComponent(GameObject* gameObject);
		void AddDragComponent(GameObject* gameObject);
		void AddChildGameObject(GameObject* child, GameObject* parent);
		GameObject* InitTestObject(Image* image);
		GameObject* NewGameObject();
		GameObject* NewGameObject(float width, float height);
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