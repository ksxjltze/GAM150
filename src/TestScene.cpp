#include "TestScene.h"
#include "TestInteractable.h"
#include "TestListener.h"
#include "DetectionListener.h"

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

}

void StarBangBang::TestScene::Free()
{
	Scene::Free();
}

void StarBangBang::TestScene::Unload()
{
	Scene::Unload();
}
