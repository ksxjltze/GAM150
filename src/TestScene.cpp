#include "TestScene.h"
#include "TestInteractable.h"
#include "TestListener.h"
#include "DetectionListener.h"
#include "Utils.h"
#include "Movement.h"
#include "MessageBus.h"
#include "ComputerListener.h"

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
	computerSprite = graphicsManager.CreateSprite(RESOURCES::VENDING_LEFT_PATH);
	prisonerSprite = graphicsManager.CreateSprite(RESOURCES::PRISONER_F1_PATH);
	doorSprite = graphicsManager.CreateSprite(RESOURCES::BIN_PATH);
}

void StarBangBang::TestScene::Init()
{
	//computer obj (v machine)
	computerObj = objectManager.NewGameObject();
	objectManager.AddImage(computerObj, computerSprite);

	//prison obj
	prisonerObj = objectManager.NewGameObject();
	objectManager.AddImage(prisonerObj, prisonerSprite);
	objectManager.AddComponent<Movement>(prisonerObj);

	//door obj
	doorObj = objectManager.NewGameObject();
	objectManager.AddImage(doorObj, doorSprite);
	doorObj->transform.position={ (float)AEGetWindowWidth() / -8, (float)AEGetWindowHeight() / 8 };
	ComputerListener &listenerComponent2 = objectManager.AddComponent<ComputerListener>(doorObj);

	MessageBus::RegisterListener(&listenerComponent2);

	//Add Listener to event system
	MessageBus::RegisterListener(&Test::listener);

	//Create new game object to listen for events
	GameObject* listenerObj = objectManager.NewGameObject();

	//Attach Listener Component
	objectManager.AddComponent<DetectionListener>(listenerObj);

	//Get Listener Component
	DetectionListener* detectionListener = listenerObj->GetComponent<DetectionListener>();

	//DetectionListener Component inherits from ListenerComponent
	//Polymorphism allows the following line
	ListenerComponent* listenerComponent = detectionListener;

	//Listener Component inherits from Listener
	//Polymorphism allows the following line
	Listener* listenPtr = listenerComponent;

	//The following code registers the same listener 3 times
	//As a result, any events that are received will also notify the same listener 3 times.
	
	//Add Listener to event system
	MessageBus::RegisterListener(listenPtr);

	//Alternative
	MessageBus::RegisterListener(listenerComponent);

	//Alternative 2
	MessageBus::RegisterListener(detectionListener);
}

void StarBangBang::TestScene::Update()
{
	Scene::Update();
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		Transform& transform = computerObj->transform;
		if (PointRectTest(GetMouseWorldPos(), transform.position, transform.scale.x * GRAPHICS::MESH_WIDTH, transform.scale.y * GRAPHICS::MESH_HEIGHT))
		{
			Event e;
			e.id = EventId::COMPUTER_CLICK;
			e.context = std::string("\nTESTING DETECTION LISTENER\n");
			MessageBus::Notify(e);

		}

	}

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
