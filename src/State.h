#pragma once
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"

namespace StarBangBang
{
	class State
	{
	public:
		State(int id) { this->id = id; }
		inline int getID() { return id; }
		virtual void Load() = 0;
		virtual void Init() = 0;
		void Update() { objectManager.Update(); }
		void Draw() { objectManager.Draw(); }
		virtual void Free() = 0;
		virtual void Unload() = 0;
	protected:
		StarBangBang::ObjectManager objectManager;
		StarBangBang::GraphicsManager graphicsManager;
		StarBangBang::MemoryManager memoryManager{ &objectManager, &graphicsManager };
	private:
		int id;
	};

}