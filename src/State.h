#pragma once
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"
#include "ScriptManager.h"
#include "TagManager.h"
#include "GameStateManager.h"

namespace StarBangBang
{
	class State
	{
	public:
		State(int id, GameStateManager& manager) : id(id), gameStateManager(manager) {}
		virtual ~State() {};
		inline int getID() { return id; }
		virtual void Load() = 0;
		virtual void Init() = 0;
		virtual void Update() { objectManager.Update();}
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
		int id;
	};

}