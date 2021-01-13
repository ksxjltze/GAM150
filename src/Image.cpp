#include "Image.h"

TempTeam::Image::Image()
{
	this->mesh = 0;
	this->texture = 0;
	this->alpha = 255;
}

TempTeam::Image::Image(AEGfxVertexList* mesh, AEGfxTexture* texture, float alpha)
{
	this->mesh = mesh;
	this->texture = texture;
	this->alpha = alpha;
}

TempTeam::Image::Image(const char* path, float width, float height, float alpha)
{
	this->texture = AEGfxTextureLoad(path);
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-width, -height, 0x00FF00FF, 0.0f, 1.0f,
		width, -height, 0x00FFFF00, 1.0f, 1.0f,
		-width, height, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		width, -height, 0x00FFFFFF, 1.0f, 1.0f,
		width, height, 0x00FFFFFF, 1.0f, 0.0f,
		-width, height, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	this->mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(this->mesh, "Failed to create mesh 2!!");

	this->alpha = alpha;
}

void TempTeam::Image::Init(const char* path, float width, float height, float alpha)
{
	this->texture = AEGfxTextureLoad(path);
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-width, -height, 0x00FF00FF, 0.0f, 1.0f,
		width, -height, 0x00FFFF00, 1.0f, 1.0f,
		-width, height, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		width, -height, 0x00FFFFFF, 1.0f, 1.0f,
		width, height, 0x00FFFFFF, 1.0f, 0.0f,
		-width, height, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	this->mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(this->mesh, "Failed to create mesh 2!!");

	this->alpha = alpha;
}

void TempTeam::Image::Draw(AEVec2 position)
{
	// Drawing object 2 - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(this->texture, 0, 0);
	// Set Position
	AEGfxSetPosition(position.x, position.y);
	// Set Transparency
	AEGfxSetTransparency(this->alpha / 255.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(this->mesh, AE_GFX_MDM_TRIANGLES);
}

void TempTeam::Image::Exit()
{
	AEGfxTextureUnload(this->texture);
	AEGfxMeshFree(this->mesh);
}
