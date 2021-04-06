#pragma once
#include "ComponentCRTP.h"
#include "Sprite.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class UIComponent : public Component<UIComponent>
	{
	public:
		UIComponent(GameObject* gameObject, GraphicsManager&, bool rescale = true);
		UIComponent(GameObject* gameObject, Sprite s, GraphicsManager&, bool rescale = true);
		void SetColor(Color c);
		void Start();
		void Update();
		void Draw();
		bool rescale;
	private:
		Sprite sprite;
		GraphicsManager& gfxMgr;
	};
}