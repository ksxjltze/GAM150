#pragma once
#include <map>
#include <string>
#include "GameObject.h"

namespace StarBangBang
{
	class TagManager
	{
	public:
		void AddTag(GameObject& obj, std::string tag);
		GameObject& GetGameObjectByTag(std::string tag);
	private:
		std::map<std::string, GameObject&> tagList;
	};
}