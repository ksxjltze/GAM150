#pragma once
#include "ComponentCRTP.h"
#include "Sprite.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class UIComponent : public Component<UIComponent>
	{
	public:
		UIComponent(GameObject* gameObject, GraphicsManager&);
		UIComponent(GameObject* gameObject, Sprite s, GraphicsManager&);
		void SetColor(Color c);
		void Start();
		void Update();
		void Draw();
	private:
		Sprite sprite;
		GraphicsManager& gfxMgr;
	};
}