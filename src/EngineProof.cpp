#include "EngineProof.h"

namespace StarBangBang
{
	StarBangBang::EngineProof::EngineProof(int id, GameStateManager& manager) : Scene(id, manager)
	{

	}

	void StarBangBang::EngineProof::Load()
	{

	}

	void StarBangBang::EngineProof::Init()
	{
		GRAPHICS::SetBackgroundColor(Black());
	}

	void StarBangBang::EngineProof::Update()
	{
		Scene::Update();
	}

	void StarBangBang::EngineProof::Draw()
	{
		Scene::Draw();
	}

	void StarBangBang::EngineProof::Free()
	{
		Scene::Free();
	}

	void StarBangBang::EngineProof::Unload()
	{
		Scene::Unload();
	}

}
