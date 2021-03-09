#include "GraphicsManager.h"
#include "constants.h"

namespace StarBangBang
{
	namespace GRAPHICS
	{
		static bool isFullscreen = false;
		static bool enableRescale = true;
		//static AEVec2 screenScaleRatio;
		static AEVec2 screenScaleRatio = { RESOLUTION_X / TARGET_WINDOW_WIDTH, RESOLUTION_Y / TARGET_WINDOW_HEIGHT };
	}

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

	AEGfxVertexList* StarBangBang::GraphicsManager::GetMesh()
	{
		if (normalizedMesh == nullptr)
		{
			normalizedMesh = CreateMesh(GRAPHICS::MESH_WIDTH, GRAPHICS::MESH_HEIGHT);
		}
		return normalizedMesh;
	}

	StarBangBang::Sprite StarBangBang::GraphicsManager::CreateSprite(const char* filePath, float width, float height)
	{
		return Sprite(LoadTexture(filePath), CreateMesh(width, height));
	}

	StarBangBang::Sprite StarBangBang::GraphicsManager::CreateSprite(const char* filePath)
	{
		return Sprite(LoadTexture(filePath), GetMesh());
	}

	StarBangBang::Sprite StarBangBang::GraphicsManager::CreateSprite(std::string filePath, float width, float height)
	{
		return CreateSprite(filePath.c_str(), width, height);
	}

	StarBangBang::Sprite StarBangBang::GraphicsManager::CreateSprite(std::string filePath)
	{
		return CreateSprite(filePath.c_str());
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
			if (mesh)
			{
				AEGfxMeshFree(mesh);
				mesh = nullptr;
			}
		}
		normalizedMesh = nullptr;
		meshList.clear();
	}

	void StarBangBang::GRAPHICS::SetZoom(float scale)
	{
		zoom = scale;
	}

	AEVec2 GRAPHICS::GetScreenScale()
	{
		return screenScaleRatio;
	}

	float StarBangBang::GRAPHICS::GetZoom()
	{
		return zoom;
	}

	void GRAPHICS::ScaleFullscreen(AEMtx33& mtx)
	{
		if (enableRescale && isFullscreen)
		{
			AEMtx33ScaleApply(&mtx, &mtx, 1 / screenScaleRatio.x, 1 / screenScaleRatio.y);
			//AEMtx33ScaleApply(&mtx, &mtx, 1 / 2.4f, 1 / 1.8f);
		}
	}

	void GRAPHICS::InverseScaleFullscreen(AEMtx33& mtx)
	{
		if (enableRescale && isFullscreen)
		{
			AEMtx33ScaleApply(&mtx, &mtx, screenScaleRatio.x, screenScaleRatio.y);
			//AEMtx33ScaleApply(&mtx, &mtx, 1 / 2.4f, 1 / 1.8f);
		}
	}

	void StarBangBang::GRAPHICS::ToggleFullscreen()
	{
		isFullscreen = !isFullscreen;
		AEToogleFullScreen(isFullscreen);
	}

	void StarBangBang::GRAPHICS::DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 pos, AEVec2 scale, float rotation)
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		// No tint
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

		// Set texture
		AEGfxTextureSet(texture, 0, 0);

		// Transform matrix
		AEMtx33 transformMtx;

		// Set Scale
		AEMtx33 scaleMtx;
		AEMtx33Scale(&scaleMtx, scale.x, scale.y);

		// Set Rotation
		AEMtx33 rotationMtx;
		AEMtx33RotDeg(&rotationMtx, rotation);

		// Set Transform
		AEMtx33Concat(&transformMtx, &scaleMtx, &rotationMtx);
		AEMtx33TransApply(&transformMtx, &transformMtx, pos.x, pos.y);

		// Camera Zoom
		AEMtx33ScaleApply(&transformMtx, &transformMtx, zoom, zoom);

		// Fullscreen scale
		ScaleFullscreen(transformMtx);

		AEGfxSetTransform(transformMtx.m);

		// Set Transparency
		AEGfxSetTransparency(1.0f);

		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}

	void StarBangBang::GRAPHICS::SetScreenScaleRatio(float x, float y)
	{
		screenScaleRatio.x = x;
		screenScaleRatio.y = y;
	}
}



