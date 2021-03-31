#include "UIComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
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
		GRAPHICS::DrawOverlay(sprite.mesh, sprite.texture, gameObject->transform.scale, gameObject->transform.position, sprite.color);
	}

}