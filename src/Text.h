#pragma once
#include "ComponentCRTP.h"
#include <cstring>
#include "Color.h"

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
		Text(GameObject* gameObject, const std::string& s, s8 fontId, Color c = White, float scale = 1.0f, bool isWorld = true);
		TextBox textbox;
		s8 fontID;
		void SetOffset(AEVec2 offset);
		void SetText(const std::string& s);
		void SetTextBox(float width, float height);
		void SetScale(float scale);
		void Start();
		void Draw();
		void SetColor(Color c);
	private:
		AEVec2 offset{ 0, 0 };
		bool isWorld{ true };
		std::string text;
		float scale;
		Color color;

	};
}