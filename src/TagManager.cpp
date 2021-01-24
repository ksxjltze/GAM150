#include "TagManager.h"

void StarBangBang::TagManager::AddTag(GameObject& obj, std::string tag)
{
	tagList.insert(std::pair<std::string, GameObject&>(tag, obj));
}

StarBangBang::GameObject& StarBangBang::TagManager::GetGameObjectByTag(std::string tag)
{
	return tagList.at(tag);
}
