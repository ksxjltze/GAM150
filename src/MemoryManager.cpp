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

StarBangBang::MemoryManager::MemoryManager(ObjectManager* objectManager, GraphicsManager* graphicsManager, ScriptManager* scriptManager)
{
    this->objectManager = objectManager;
    this->graphicsManager = graphicsManager;
    this->scriptManager = scriptManager;
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

    assert(scriptManager);
    if (scriptManager)
    {
        scriptManager->DestroyScripts();
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