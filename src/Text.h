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
		Text(GameObject* gameObject);
		AEVec2 position;
		TextBox textbox;
		s8 fontID;
		void SetText(const std::string& s);
		void SetTextBox(float width, float height);
		void Draw();
	private:
		std::string text;


	};
}