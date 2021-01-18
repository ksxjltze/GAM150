#include "ObjectManager.h"
#include "Utils.h"

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

void StarBangBang::ObjectManager::AddImageComponent(GameObject* gameObject, AEGfxTexture* texture, AEGfxVertexList* mesh)
{
	if (mesh != nullptr && texture != nullptr)
	{
		ImageComponent image = ImageComponent(gameObject, mesh, texture);
		imageComponentList.push_back(image);
	}
}

void StarBangBang::ObjectManager::AddImageComponent(GameObject* gameObject, Sprite sprite)
{
	if (sprite.mesh != nullptr && sprite.texture != nullptr)
	{
		ImageComponent image = ImageComponent(gameObject, sprite.mesh, sprite.texture);
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
	imageComponentList.clear();
	transformComponentList.clear();
	dragComponentList.clear();
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
