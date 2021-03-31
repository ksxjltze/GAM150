#include "UIComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	const static float FULLSCREEN_SCALE = 2.0f;

	UIComponent::UIComponent(GameObject* gameObject, Sprite s) : Component(gameObject), sprite{ s }
	{

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

			GRAPHICS::DrawOverlay(sprite.mesh, sprite.texture, scale, gameObject->transform.position, sprite.color);

		}
	}

}