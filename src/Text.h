#pragma once
#include "ComponentCRTP.h"
#include <cstring>


namespace StarBangBang
{

	class TextBox
	{
	public:
		float width = 150.f;
		float height = 150.f;

	};

	class Text: public Component<Text>
	{
	public:
		AEVec2 position;
		TextBox textbox;
		s8 fontID;
		Text(GameObject* gameObject);
		void Draw();
	private:
		std::string text;


	};
}