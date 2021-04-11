/******************************************************************************/
/*!
\title		Captain Stealth
\file		State.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		State class. Represents one scene/state of the game.
			Is responsible for facilitating game behavior.
			Contains an Object Manager, Graphics Manager and Memory Manager instance.
			Contains core functions Init, Load, Update, Draw, Free and Unload.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"
#include "GameStateManager.h"
#include "MessageBus.h"

namespace StarBangBang
{
	class Scene
	{
	public:
		Scene(int id, GameStateManager& gsm) : id(id), gameStateManager(gsm) {}
		virtual ~Scene() {};
		inline int getID() { return id; }

		virtual void Load() = 0;
		void Start() { objectManager.Init(); }
		virtual void Init() = 0;
		virtual void Update() 
		{ 
			objectManager.Update(); 
			objectManager.LateUpdate(); 
		}
		virtual void Draw() { objectManager.Draw(); }
		virtual void Free() { memoryManager.Free(); CollisionManager::Free(); }
		virtual void Unload() { memoryManager.Unload(); MessageBus::Reset(); }

	protected:
		friend class GameStateManager;
		GraphicsManager graphicsManager;
		ObjectManager objectManager;
		MemoryManager memoryManager{ &objectManager, &graphicsManager };
		GameStateManager& gameStateManager;
		const int id;
	};

}