#include "MemoryManager.h"

StarBangBang::MemoryManager::MemoryManager(ObjectManager* objectManager, GraphicsManager* graphicsManager)
{
    this->objectManager = objectManager;
    this->graphicsManager = graphicsManager;
}

void StarBangBang::MemoryManager::Load()
{

}

void StarBangBang::MemoryManager::Free()
{
    objectManager->FreeComponents();
    objectManager->FreeObjects();
}

void StarBangBang::MemoryManager::Unload()
{
    graphicsManager->UnloadTextures();
    graphicsManager->FreeMeshes();
}