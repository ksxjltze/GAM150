#include "Text.h"
#include "GraphicsManager.h"

using namespace StarBangBang;


Text::Text(GameObject* gameObject) : Component(gameObject), position{ AEVec2{0,0} }, textbox{ TextBox() }, fontID{-1}, text{ std::string("HELO") }
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

	AEMtx33 camera = GRAPHICS::GetCameraMatrix();

	position = gameObject->GetPos();
	AEMtx33MultVec(&position, &camera, &position );

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	const float f_scale = 2.0f;

	float y_offset = 0.3f;

	f32 TextWidth, TextHeight;
	s8* str = (s8*)text.c_str();
	AEGfxGetPrintSize(fontID, str, f_scale, TextWidth, TextHeight);
	AEGfxPrint(fontID, str, position.x - TextWidth / 2, position.y + y_offset - TextHeight / 2, f_scale, 1.0f, 1.0f ,1.0f);


	//float c_w = 12.0f/ AEGetWindowWidth() * f_scale * 0.5f * 4;
	//AEGfxPrint(fontID, (s8*)text.c_str(), position.x -c_w , position.y + 0.2f, f_scale, 1.0f, 1.0f ,1.0f);
}
