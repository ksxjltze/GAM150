#include "Text.h"
#include "GraphicsManager.h"

using namespace StarBangBang;


Text::Text(GameObject* gameObject) : Component(gameObject), textbox{ TextBox() }, fontID{ -1 }, text{ std::string("HELO") }, scale{ 1.0f }
{

}

StarBangBang::Text::Text(GameObject* gameObject, const std::string& s, s8 fontId, Color c, float scale) : Component(gameObject), textbox{ TextBox() }, fontID{ fontId }, text{ s }, scale{ scale }, color{ c }
{

}

void StarBangBang::Text::SetText(const std::string& s)
{
	text = s;
}

void StarBangBang::Text::SetTextBox(float width, float height)
{
	textbox.width = width;
	textbox.height = height;
}

void Text::Draw()
{
	if (fontID == -1)
		return;

	if (!gameObject->active)
		return;

	AEMtx33 camera = GRAPHICS::GetCameraMatrix();

	AEVec2 position = gameObject->GetPos();
	AEMtx33MultVec(&position, &camera, &position );

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	f32 TextWidth, TextHeight;
	s8* str = (s8*)text.c_str();

	//float wWidth = AEGetWindowWidth();
	//float wHeight = AEGetWindowHeight();
	float wWidth = static_cast<float>(AEGetWindowWidth());
	float wHeight = static_cast<float>(AEGetWindowHeight());

	float textScale = scale;
	AEVec2 screenScale = GRAPHICS::GetScreenScale();

	textScale *= screenScale.x / screenScale.y;

	AEGfxGetPrintSize(fontID, str, textScale, TextWidth, TextHeight);
	//AEGfxPrint
	//(fontID, str, 0.0f - TextWidth / 2, 0.0f - TextHeight / 2,
	//	scale, 1.0f, 1.0f, 1.0f
	//);
	AEGfxPrint
	(fontID, str, 
		position.x / wWidth * 2 - TextWidth / 2, 
		position.y / wHeight * 2 - TextHeight / 2, 
		textScale, color.R(), color.G(), color.B()
	);
}

void StarBangBang::Text::SetColor(Color c)
{
	color = c;
}
