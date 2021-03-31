#pragma once
#include "ComponentCRTP.h"
#include "Sprite.h"

namespace StarBangBang
{
	class UIComponent : public Component<UIComponent>
	{
	public:
		UIComponent(GameObject* gameObject, Sprite s);
		void Start();
		void Update();
		void Draw();
	private:
		Sprite sprite;
	};
}