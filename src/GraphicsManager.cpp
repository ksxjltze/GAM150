#include "GraphicsManager.h"

AEGfxTexture* TempTeam::GraphicsManager::LoadTexture(const char* filePath)
{
    AEGfxTexture* texture = AEGfxTextureLoad(filePath);
    AE_ASSERT_MESG(texture, "Failed to load texture!!");
    if (texture)
        return texture;

    return nullptr;
}

AEGfxVertexList* TempTeam::GraphicsManager::CreateMesh(float width, float height)
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
		return mesh;

    return nullptr;
}
