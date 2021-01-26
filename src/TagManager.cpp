#include "TagManager.h"
#include <iostream>

void StarBangBang::TagManager::AddTag(GameObject& obj, std::string tag)
{
	tagList.insert(std::pair<std::string, GameObject&>(tag, obj));
}

StarBangBang::GameObject& StarBangBang::TagManager::GetGameObjectByTag(std::string tag)
{
	try
	{
		return tagList.at(tag);
	}
	catch(const std::out_of_range& err)
	{
		std::cout << "Unable to find Tag " << tag << std::endl;
		std::cout << "Out of range error: " << err.what() << std::endl;
	}
}
