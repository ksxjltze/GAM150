#include "ScriptManager.h"

void StarBangBang::ScriptManager::DestroyScripts()
{
	for (Script* s : scriptList)
	{
		delete s;
		s = nullptr;
	}
	scriptList.clear();
}

void StarBangBang::ScriptManager::Start()
{
	for (Script* s : scriptList)
	{
		s->Start();
	}
}

void StarBangBang::ScriptManager::Update()
{
	for (Script* s : scriptList)
	{
		if (s->active)
			s->Update();
	}
}