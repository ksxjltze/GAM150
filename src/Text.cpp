#include "Text.h"
#include "GraphicsManager.h"

using namespace StarBangBang;


Text::Text(GameObject* gameObject) : Component(gameObject), position{ AEVec2{0,0} }, textbox{ TextBox() }, fontID{-1}, text{ std::string("HELO") }
{

}

void Text::Draw()
{
	if (fontID == -1)
		return;

	AEMtx33 camera = GRAPHICS::GetCameraMatrix();

	position = gameObject->GetPos();
	AEMtx33MultVec(&position, &camera, &position );

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	const float f_scale = 10.0f;
	float c_w = 12.0f/ AEGetWindowWidth() * f_scale * 0.5f * 4;

	AEGfxPrint(fontID, (s8*)text.c_str(), position.x -c_w , position.y, f_scale, 1.0f, 1.0f ,1.0f);
}
