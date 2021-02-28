#include "GuardManager.h"
#include "Guard.h"

using namespace StarBangBang;

GuardManager::GuardManager(ObjectManager& _manager, Sprite& _sprite)
	: objectManager(&_manager), guard_sprite(&_sprite)
{
	Start();
}

GuardManager::~GuardManager()
{
	guards.clear();
}

void GuardManager::Start()
{
	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		guards.push_back(objectManager->NewGameObject());
		guards[i]->SetPos({ 100, 100 });
		objectManager->AddImage(guards[i], *guard_sprite);
		objectManager->AddComponent<Guard>(guards[i]);
		objectManager->AddComponent<GuardMovement>(guards[i]);
		objectManager->AddComponent<GuardVision>(guards[i]);
	}
}

void GuardManager::Update()
{
	for (size_t i = 0; i < NUM_GUARDS; i++)
	{

	}
}