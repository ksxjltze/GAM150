#pragma once
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"
#include "TagManager.h"
#include "GameStateManager.h"

namespace StarBangBang
{
	class Scene
	{
	public:
		Scene(int id, GameStateManager& gsm) : id(id), gameStateManager(gsm) {}
		virtual ~Scene() {};
		inline int getID() { return id; }
		virtual void Load() = 0;
		virtual void Init() = 0;
		virtual void Update() 
		{ 
			objectManager.Update(); 
			objectManager.LateUpdate(); 
		}
		virtual void Draw() { objectManager.Draw(); }
		virtual void Free() { memoryManager.Free(); }
		virtual void Unload() { memoryManager.Unload(); }
	protected:
		friend class GameStateManager;
		StarBangBang::GraphicsManager graphicsManager;
		StarBangBang::ObjectManager objectManager;
		StarBangBang::TagManager tagManager;
		StarBangBang::MemoryManager memoryManager{ &objectManager, &graphicsManager };
		GameStateManager& gameStateManager;
		const int id;
	};

}