#include "TestScene.h"
#include "TestInteractable.h"
#include "TestListener.h"
#include "DetectionListener.h"
#include "Utils.h"
#include "Movement.h"
#include "MessageBus.h"
#include "ComputerListener.h"
#include "ComputerScript.h"
#include "CameraComponent.h"
#include "CollisionListener.h"
#include "CaptainStealth.h"


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
	computerSprite = graphicsManager.CreateSprite(RESOURCES::COMPUTER_PATH);
	prisonerSprite = graphicsManager.CreateSprite(RESOURCES::PRISONER_F1_PATH);
	doorSprite = graphicsManager.CreateSprite(RESOURCES::DOOR_PATH);
}

void StarBangBang::TestScene::Init()
{

	for (int i = 0; i < 7; ++i)
	{
		CaptainStealth::SpawnComputer(objectManager, computerSprite, { i * 100.0f, 0 });
	}


	//prison obj
	GameObject* player;
	CaptainStealth::SpawnPlayer(objectManager, player, prisonerSprite);
	player->transform.position = { 0, 0 };

	//door obj
	CaptainStealth::SpawnDoor(objectManager, doorSprite, { (float)AEGetWindowWidth() / -8, (float)AEGetWindowHeight() / 8 });


}

void StarBangBang::TestScene::Update()
{
	Scene::Update();

	//Send message on key press (T)
	if (AEInputCheckTriggered(AEVK_T))
	{
		Test::interactableObject.Interact();
	}

	//Send DETECTION Message on key press (E)
	if (AEInputCheckTriggered(AEVK_E))
	{
		Event detectionEvent;
		detectionEvent.id = EventId::DETECTED;
		detectionEvent.context = std::string("\nTESTING DETECTION LISTENER\n");

		MessageBus::Notify(detectionEvent);
	}
}

void StarBangBang::TestScene::Draw()
{
	Scene::Draw();
}

void StarBangBang::TestScene::Free()
{
	Scene::Free();
}

void StarBangBang::TestScene::Unload()
{
	Scene::Unload();
}
