#include "DebugText.h"
#include <iostream>
#include "GraphicsManager.h"
#include "globals.h"

StarBangBang::DebugText::DebugText(GameObject* obj, s8 fontId) :
	ListenerComponent(obj), fontId{ fontId }, fontScale{ 1.0f }, textPos{ 0, 0.8f }, duration{ 4.0f }, timer{ 0.0f }, fadeStart{ 2.0f }
{
}

void StarBangBang::DebugText::SetFont(s8 id)
{
	fontId = id;
}

void StarBangBang::DebugText::SetTextbox(float width, float height)
{
	textbox.width = width;
	textbox.height = height;
}

void StarBangBang::DebugText::onNotify(Event e)
{
	if (e.id == EventId::PRINT_TEXT)
	{
		std::string message = std::any_cast<std::string>(e.context);
		std::cout << message << std::endl;
		text = message;
		timer = duration;
	}
}

void StarBangBang::DebugText::Update()
{
	if (timer > 0)
	{
		timer -= g_dt;
	}
	else
	{
		timer = -1.0f;
		text = "";
	}
}

void StarBangBang::DebugText::Draw()
{
	if (fontId == -1 || timer <= 0.0f)
		return;

	AEGfxSetBlendMode(AE_GFX_BM_BLEND); 
	s8* str = const_cast<s8*>(text.c_str());
	float color = timer / (duration - fadeStart);

	//magic numbers for now
	if (color <= 0.1f)
		color = 0.1f;

	f32 TextWidth, TextHeight;
	AEGfxGetPrintSize(fontId, str, fontScale, TextWidth, TextHeight);
	AEGfxPrint(fontId, str, textPos.x - TextWidth / 2, textPos.y - TextHeight / 2, fontScale, color, color, color);
}