#pragma once
#include "ScriptComponent.h"
#include <vector>

namespace StarBangBang
{
	class ScriptManager
	{
	public:
		template <class ScriptType>
		inline Script* NewScript(GameObject* gameObject)
		{
			ScriptType* script = new ScriptType(gameObject);
			scriptList.push_back(script);
			return script;
		}
		
		//To be removed
		template <class ScriptType>
		inline Script* AddScript(GameObject* gameObject)
		{
			ScriptType* script = new ScriptType(gameObject);
			scriptList.push_back(script);
			return script;
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

		inline void Start()
		{
			for (Script* s : scriptList)
			{
				s->Start();
			}
		}

		inline void Update()
		{
			for (Script* s : scriptList)
			{
				s->Update();
			}
		}

	private:
		friend class ObjectManager;
		std::vector<Script*> scriptList;
	};
}