#include "TestScene.h"
#include "TestInteractable.h"
#include "TestListener.h"

namespace StarBangBang
{
	namespace Test
	{
		static TestInteractable interactableObject;
		static TestListener     listener;
	}
}

StarBangBang::TestScene::TestScene(int id, GameStateManager& gsm) : Scene(id, gsm)
{

}

void StarBangBang::TestScene::Load()
{

}

void StarBangBang::TestScene::Init()
{
	//Add Listener to event system
	MessageBus::RegisterListener(&Test::listener);
}

void StarBangBang::TestScene::Update()
{
	//Send message on key press (T)
	if (AEInputCheckTriggered(AEVK_T))
	{
		Test::interactableObject.Interact();
	}
}

void StarBangBang::TestScene::Draw()
{

}

void StarBangBang::TestScene::Free()
{

}

void StarBangBang::TestScene::Unload()
{

}
