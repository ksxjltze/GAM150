#include "Sample_Scene.h"
#include "CollisionManager.h"
#include "MovementManager.h"
#include "Click.h"
#include "CameraComponent.h"

void Testt()
{
	PRINT("TESTES\n");
}

StarBangBang::Sample_Scene::Sample_Scene(int id, GameStateManager& manager) : Scene(id, manager), gameObject{nullptr}
{
	
}

void StarBangBang::Sample_Scene::Load()
{
	image = graphicsManager.CreateSprite("./Resources/PlanetTexture.png");
	image2 = graphicsManager.CreateSprite("./Resources/boi.png");
}

void StarBangBang::Sample_Scene::Init()
{
	GRAPHICS::SetBackgroundColor(SkyBlue);
	gameObject = objectManager.NewGameObject();

	//objectManager.AddImage(gameObject, image2);
	objectManager.AddComponent<ImageComponent>(gameObject, image2);
	MovementManager& moveMgr = objectManager.AddComponent<MovementManager>(gameObject);
	objectManager.AddCollider(gameObject, false);
	//objectManager.AddComponent<Click>(gameObject).setCallback(Testt);
	objectManager.AddComponent<PrimaryMovementController>(gameObject);
	objectManager.AddComponent<CameraComponent>(gameObject);
	objectManager.AddComponent<RigidBody>(gameObject);
	gameObject->GetComponent<RigidBody>()->SetMass(0);
	moveMgr.AddController(gameObject);

	int nObjects = 8;
	for (int i = 0; i < nObjects; i++)
	{
		GameObject* obj = objectManager.NewGameObject();

		double rads = (2 * (double)PI / nObjects) * i;
		AEVec2& pos = obj->transform.position;

		pos.x = static_cast<float>(cos(rads) * 300);
		pos.y = static_cast<float>(sin(rads) * 300);

		objectManager.AddComponent<RigidBody>(obj);
		objectManager.AddImage(obj, image);
		objectManager.AddCollider(obj, false);
		objectManager.AddComponent<PrimaryMovementController>(obj);

		moveMgr.AddController(obj);

	}

	objectManager.Init();
}

void StarBangBang::Sample_Scene::Update()
{
	if (AEInputCheckTriggered(AEVK_SPACE))
	{
		gameStateManager.SetNextGameState(SceneID::DEMO);
	}
	Scene::Update();
}

void StarBangBang::Sample_Scene::Draw()
{
	Scene::Draw();
}

void StarBangBang::Sample_Scene::Free()
{
	Scene::Free();
}

void StarBangBang::Sample_Scene::Unload()
{
	Scene::Unload();
	
}


