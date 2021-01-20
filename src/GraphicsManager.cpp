#include "GraphicsManager.h"

AEGfxTexture* StarBangBang::GraphicsManager::LoadTexture(const char* filePath)
{
    AEGfxTexture* texture = AEGfxTextureLoad(filePath);
    AE_ASSERT_MESG(texture, "Failed to load texture!!");

	if (texture)
	{
		textureList.push_back(texture);
        return texture;
	}

    return nullptr;
}

AEGfxVertexList* StarBangBang::GraphicsManager::CreateMesh(float width, float height)
{
	AEGfxVertexList* mesh;
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-width / 2, -height / 2, 0, 0.0f, 1.0f,
		width / 2, -height / 2, 0, 1.0f, 1.0f,
		-width / 2, height / 2, 0, 0.0f, 0.0f);

	AEGfxTriAdd(
		width / 2, -height / 2, 0, 1.0f, 1.0f,
		width / 2, height / 2, 0, 1.0f, 0.0f,
		-width / 2, height / 2, 0, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(mesh, "Failed to create mesh!!");

	if (mesh)
	{
		meshList.push_back(mesh);
		return mesh;
	}

    return nullptr;
}

void StarBangBang::GraphicsManager::UnloadTextures()
{
	for (AEGfxTexture* texture : textureList)
	{
		AEGfxTextureUnload(texture);
		texture = nullptr;
	}
	textureList.clear();
}

void StarBangBang::GraphicsManager::FreeMeshes()
{
	for (AEGfxVertexList* mesh : meshList)
	{
		AEGfxMeshFree(mesh);
		mesh = nullptr;
	}
	meshList.clear();
}

void StarBangBang::DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 pos)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(texture, 0, 0);
	// Set Position
	AEGfxSetPosition(pos.x, pos.y);
	// Set Transparency
	AEGfxSetTransparency(1.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

