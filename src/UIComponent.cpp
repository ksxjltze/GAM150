#include "UIComponent.h"

namespace StarBangBang
{
	const static float FULLSCREEN_SCALE = 2.0f;



	UIComponent::UIComponent(GameObject* gameObject, GraphicsManager& gfx, bool rescale) : Component(gameObject), gfxMgr{ gfx }, rescale{ rescale }
	{

	}

	UIComponent::UIComponent(GameObject* gameObject, Sprite s, GraphicsManager& gfx, bool rescale) : Component(gameObject), sprite{ s }, gfxMgr{ gfx }, rescale{ rescale }
	{

	}

	void UIComponent::SetColor(Color c)
	{
		sprite.color = c;
	}

	void UIComponent::Start()
	{

	}

	void UIComponent::Update()
	{

	}

	void UIComponent::Draw()
	{
		if (gameObject->active)
		{
			AEVec2 scale = gameObject->transform.scale;

			if (sprite.mesh)
				GRAPHICS::DrawOverlay(sprite.mesh, sprite.texture, scale, gameObject->transform.position, sprite.color, rescale);
			else
				GRAPHICS::DrawOverlay(gfxMgr.GetMesh(), nullptr, scale, gameObject->transform.position, sprite.color, rescale);

		}
	}

}