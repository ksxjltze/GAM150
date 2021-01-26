#pragma once
#include "ScriptComponent.h"
#include <vector>

namespace StarBangBang
{
	class ScriptManager
	{
	public:
		void Start();
		void Update();

	private:
		friend class ObjectManager;
		friend class MemoryManager;

		template <class ScriptType>
		inline Script* NewScript(GameObject* gameObject)
		{
			ScriptType* script = new ScriptType(gameObject);
			scriptList.push_back(script);
			return script;
		}
		void AddScript(Script* script);
		void DestroyScripts();
		std::vector<Script*> scriptList;
	};
}