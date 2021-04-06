#include "UIComponent.h"

namespace StarBangBang
{
	const static float FULLSCREEN_SCALE = 2.0f;



	UIComponent::UIComponent(GameObject* gameObject, GraphicsManager& gfx, bool rescale) : Component(gameObject), transparency{1.0f}, gfxMgr{ gfx }, rescale{ rescale }
	{

	}

	UIComponent::UIComponent(GameObject* gameObject, Sprite s, GraphicsManager& gfx, bool rescale) : Component(gameObject), transparency{ 1.0f } ,sprite{ s }, gfxMgr{ gfx }, rescale{ rescale }
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

	void UIComponent::SetTransparency(float a)
	{
		transparency = a;
	}

	void UIComponent::Draw()
	{
		if (gameObject->active)
		{
			AEGfxSetTransparency(transparency);

			AEVec2 scale = gameObject->transform.scale;

			if (sprite.texture)
				GRAPHICS::DrawOverlay(gfxMgr.GetMesh(), sprite.texture, scale, gameObject->transform.position, sprite.color, rescale);
			else
				GRAPHICS::DrawOverlay(gfxMgr.GetMesh(), nullptr, scale, gameObject->transform.position, sprite.color, rescale);
			AEGfxSetTransparency(1.0f);

		}
	}

}