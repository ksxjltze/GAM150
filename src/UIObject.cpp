#include "UIObject.h"
#include "GraphicsManager.h"
#include "Component.h"

namespace StarBangBang
{
	UIObject::UIObject() : GameObject()
	{

	}

	void UIObject::Update()
	{
		for (auto& component : componentList)
		{
			component->Update();
		}

	}

	void UIObject::Draw()
	{
		GRAPHICS::DrawOverlay(s.mesh, s.texture, transform.scale, transform.position, s.color);
	}
}