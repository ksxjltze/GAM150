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
		virtual void Update() { objectManager.Update();}
		virtual void Draw() { objectManager.Draw(); }
		virtual void Free() { memoryManager.Free(); }
		virtual void Unload() { memoryManager.Unload(); }
	protected:
		StarBangBang::GraphicsManager graphicsManager;
		StarBangBang::ObjectManager objectManager;
		StarBangBang::TagManager tagManager;
		StarBangBang::MemoryManager memoryManager{ &objectManager, &graphicsManager };
	private:
		friend class GameStateManager;
		int id;
	};

}