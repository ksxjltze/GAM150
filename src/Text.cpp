#include "Text.h"
#include "GraphicsManager.h"
#include "constants.h"

using namespace StarBangBang;


Text::Text(GameObject* gameObject) : Component(gameObject), textbox{ TextBox() }, fontID{ -1 }, text{ std::string("HELO") }, scale{ 1.0f }
{
	gameObject->SetLayer(LAYER::UI);
}

StarBangBang::Text::Text(GameObject* gameObject, const std::string& s, s8 fontId, Color c, float scale, bool isWorld) : Component(gameObject), textbox{ TextBox() }, fontID{ fontId }, text{ s }, scale{ scale }, color{ c }, isWorld{ isWorld }
{
	gameObject->SetLayer(LAYER::UI);
}

void StarBangBang::Text::SetOffset(AEVec2 newOffset)
{
	offset = newOffset;
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

void StarBangBang::Text::SetScale(float newScale)
{
	scale = newScale;
}

void StarBangBang::Text::Start()
{

}

void Text::Draw()
{
	if (fontID == -1)
		return;

	if (!gameObject->active)
		return;

	AEMtx33 camera = GRAPHICS::GetCameraMatrix();

	AEVec2 position = gameObject->GetPos();
	position.x += offset.x;
	position.y += offset.y;

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	f32 TextWidth, TextHeight;
	s8* str = (s8*)text.c_str();

	//float wWidth = AEGetWindowWidth();
	//float wHeight = AEGetWindowHeight();
	float wWidth = static_cast<float>(AEGetWindowWidth());
	float wHeight = static_cast<float>(AEGetWindowHeight());

	if (isWorld)
	{
		AEMtx33MultVec(&position, &camera, &position);
		float textScale = scale / 2;
		AEVec2 screenScale = GRAPHICS::GetScreenScale();

		if (GRAPHICS::IsFullscreen())
			textScale /= 2;

		AEGfxGetPrintSize(fontID, str, textScale, TextWidth, TextHeight);
		AEGfxPrint
		(fontID, str, 
			position.x / wWidth * 2 - TextWidth / 2, 
			position.y / wHeight * 2 - TextHeight / 2, 
			textScale, color.R(), color.G(), color.B()
		);

	}
	else
	{
		AEGfxGetPrintSize(fontID, str, scale, TextWidth, TextHeight);
		AEGfxPrint
		(fontID, str,
			position.x - TextWidth / 2,
			position.y - TextHeight / 2,
			scale, color.R(), color.G(), color.B()
		);
	}
}

void StarBangBang::Text::SetColor(Color c)
{
	color = c;
}
