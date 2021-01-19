#include "MemoryManager.h"

StarBangBang::MemoryManager::MemoryManager()
{
    objectManager = nullptr;
    graphicsManager = nullptr;
}

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
    assert(objectManager);
    if (objectManager)
    {
        objectManager->FreeComponents();
        objectManager->FreeObjects();
    }
        
}

void StarBangBang::MemoryManager::Unload()
{
    assert(graphicsManager);
    if (graphicsManager)
    {
        graphicsManager->UnloadTextures();
        graphicsManager->FreeMeshes();
    }
}