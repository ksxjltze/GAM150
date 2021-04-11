/******************************************************************************/
/*!
\title		Captain Stealth
\file		MemoryManager.h
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

#pragma once
#include "ObjectManager.h"

namespace StarBangBang
{
	class MemoryManager
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Default Constructor.
		***************************************************************************/
		MemoryManager();

		/*!*************************************************************************
		 * \brief 
		 * Constructor, sets the pointers to the
		 * object manager and graphics manager objects of the scene.
		 * 
		 * \param objectManager
		 * Pointer to the object manager.
		 * \param graphicsManager
		 * Pointer to the graphics manager.
		***************************************************************************/
		MemoryManager(ObjectManager* objectManager, GraphicsManager* graphicsManager);

		/*!*************************************************************************
		 * \brief 
		 * Frees the game objects and components created by the object manager.
		 * \return
		 * void
		***************************************************************************/
		void Free();
		
		/*!*************************************************************************
		 * \brief 
		 * Unloads and destroys the textures and meshes created by the
		 * graphics manager.
		 * \return
		 * void
		***************************************************************************/
		void Unload();
	
	private:
		ObjectManager* objectManager;
		GraphicsManager* graphicsManager;
	};
}