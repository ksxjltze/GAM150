#include "UIComponent.h"

namespace StarBangBang
{
	const static float FULLSCREEN_SCALE = 2.0f;



	UIComponent::UIComponent(GameObject* gameObject, GraphicsManager& gfx) : Component(gameObject), gfxMgr{ gfx }
	{

	}

	UIComponent::UIComponent(GameObject* gameObject, Sprite s, GraphicsManager& gfx) : Component(gameObject), sprite{ s }, gfxMgr{ gfx }
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

			if (GRAPHICS::IsFullscreen())
			{
				AEVec2 screenRatio = GRAPHICS::GetScreenScale();

				scale.x *= screenRatio.x * FULLSCREEN_SCALE;
				scale.y *= screenRatio.y * FULLSCREEN_SCALE;
			}

			if (sprite.mesh)
				GRAPHICS::DrawOverlay(sprite.mesh, sprite.texture, scale, gameObject->transform.position, sprite.color);
			else
				GRAPHICS::DrawOverlay(gfxMgr.GetMesh(), nullptr, scale, gameObject->transform.position, sprite.color);

		}
	}

}