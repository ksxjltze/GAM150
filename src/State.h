#pragma once
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"
#include "ScriptManager.h"
#include "TagManager.h"

namespace StarBangBang
{
	class State
	{
	public:
		State(int id) { this->id = id;}
		virtual ~State() {};
		inline int getID() { return id; }
		virtual void Load() = 0;
		virtual void Init() = 0;
		virtual void Update() { objectManager.Update(); scriptManager.Update(); }
		virtual void Draw() { objectManager.Draw(); }
		virtual void Free() = 0;
		virtual void Unload() = 0;
	protected:
		StarBangBang::GraphicsManager graphicsManager;
		StarBangBang::ObjectManager objectManager;
		StarBangBang::ScriptManager& scriptManager { objectManager.scriptManager };
		StarBangBang::TagManager tagManager;
		//StarBangBang::MemoryManager memoryManager{ &objectManager, &graphicsManager };
		StarBangBang::MemoryManager memoryManager{ &objectManager, &graphicsManager, &scriptManager };
	private:
		friend class GameStateManager;
		int id;
	};

}