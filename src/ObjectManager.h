#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "TransformComponent.h"
#include "DragComponent.h"
#include "Sprite.h"
#include <vector>

namespace StarBangBang
{
	class ObjectManager
	{
	public:
		void AddImageComponent(GameObject* gameObject, GraphicsManager& graphicsManager, const char* spritePath);
		void AddImageComponent(GameObject* gameObject, AEGfxTexture* texture, AEGfxVertexList* mesh);
		void AddImageComponent(GameObject* gameObject, Sprite sprite);
		void AddTransformComponent(GameObject* gameObject);
		void AddDragComponent(GameObject* gameObject);
		void AddChildGameObject(GameObject* child, GameObject* parent);
		//GameObject* InitTestObject(Image* image);
		GameObject* NewGameObject();
		GameObject* NewGameObject(float width, float height);
		void FreeObjects();
		void FreeComponents();
		void Draw();
		void Update();
	private:
		std::vector<GameObject*> gameObjectList;
		std::vector<ImageComponent> imageComponentList;
		std::vector<TransformComponent> transformComponentList;
		std::vector<DragComponent> dragComponentList;
	};
}