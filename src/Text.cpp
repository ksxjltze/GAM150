#include "Text.h"
#include "GraphicsManager.h"
#include "constants.h"

using namespace StarBangBang;


/*!*************************************************************************
 * \brief
 * Component Constructor.
 * Attaches the component to a game object.
 * \param gameObject
 * GameObject to attach to.
***************************************************************************/
Text::Text(GameObject* gameObject) : Component(gameObject), textbox{ TextBox() }, fontID{ -1 }, text{ std::string("HELO") }, scale{ 1.0f }
{
	gameObject->SetLayer(LAYER::UI);
}

/*!*************************************************************************
 * \brief
 * Component Constructor.
 * Attaches the component to a game object.
 * Sets the text string, font, color and scale of the text object.
 *
 * \param gameObject
 * GameObject to attach to.
 *
 * \param textString
 * String to display.
 *
 * \param fontId
 * Font to use.
 *
 * \param textColor
 * Color of the text.
 *
 * \param textScale
 * Scale of the text.
 *
 * \param isWorld
 * Whether the text object should use world position or screen position (Percentage)
***************************************************************************/
StarBangBang::Text::Text(GameObject* gameObject, const std::string& textString, s8 fontId, Color textColor, float textScale, bool isWorld) : Component(gameObject), textbox{ TextBox() }, fontID{ fontId }, text{ textString }, scale{ textScale }, color{ textColor }, isWorld{ isWorld }
{
	gameObject->SetLayer(LAYER::UI);
}

/*!*************************************************************************
 * \brief
 * Sets the offset from the game object position.
 * \param offset
 * Vector to offset by.
***************************************************************************/
void StarBangBang::Text::SetOffset(AEVec2 newOffset)
{
	offset = newOffset;
}

/*!*************************************************************************
 * \brief
 * Sets the text to display.
 * \param textString
 * String to display.
***************************************************************************/
void StarBangBang::Text::SetText(const std::string& s)
{
	text = s;
}

/*!*************************************************************************
 * \brief
 * Sets the textbox dimensions.
 * \param width Width of the textbox.
 * \param height Height of the textbox.
***************************************************************************/
void StarBangBang::Text::SetTextBox(float width, float height)
{
	textbox.width = width;
	textbox.height = height;
}

/*!*************************************************************************
 * \brief
 * Sets the scale of the text.
 * \param textScale
 * Scale of the text.
***************************************************************************/
void StarBangBang::Text::SetScale(float newScale)
{
	scale = newScale;
}

/*!*************************************************************************
 * \brief
 * Start function. Called once at the start of the scene.
***************************************************************************/
void StarBangBang::Text::Start()
{

}

/*!*************************************************************************
 * \brief
 * Draw function. Called once every frame.
***************************************************************************/
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

/*!*************************************************************************
 * \brief
 * Sets the color of the text.
 * \param textColor
 * Color to set.
***************************************************************************/
void StarBangBang::Text::SetColor(Color textColor)
{
	color = textColor;
}
