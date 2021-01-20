#include "Player.h"

void StarBangBang::Player::Load(GraphicsManager& gfxManager)
{
	gameObject = nullptr;
	image.texture = gfxManager.LoadTexture("../Resources/boi.png");
	image.mesh = gfxManager.CreateMesh(100, 100);
}

void StarBangBang::Player::Start(ObjectManager& objManager)
{
	gameObject = objManager.NewGameObject(100, 100);
	objManager.AddImageComponent(gameObject, image);
	objManager.AddComponent<DragComponent>(gameObject);
}

void StarBangBang::Player::Update()
{

}
