#pragma once
#include "ScriptComponent.h"
#include <vector>

namespace StarBangBang
{
	class ScriptManager
	{
	public:
		template <class ScriptType>
		inline void AddScript(GameObject* gameObject)
		{
			ScriptType* script = new ScriptType(gameObject);
			scriptList.push_back(script);
		}

		inline void DestroyScripts()
		{
			for (Script* s : scriptList)
			{
				delete s;
				s = nullptr;
			}
			scriptList.clear();
		}

		inline void Update()
		{
			for (Script* s : scriptList)
			{
				s->Update();
			}
		}

	private:
		std::vector<Script*> scriptList;
	};
}