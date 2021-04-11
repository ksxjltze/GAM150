/******************************************************************************/
/*!
\title		Captain Stealth
\file		MemoryManager.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		MemoryManager class.
            Manages the memory allocated by Object Manager (for game objects)
            and Graphics Manager (for textures and meshes) and frees/unloads
            them at the end of each scene's lifetime.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

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
    if (objectManager)
    {
        objectManager->FreeComponents();
        objectManager->FreeObjects();
    }
        
}

void StarBangBang::MemoryManager::Unload()
{
    if (graphicsManager)
    {
        graphicsManager->UnloadTextures();
        graphicsManager->FreeMeshes();
    }
}