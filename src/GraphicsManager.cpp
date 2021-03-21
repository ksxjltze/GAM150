#include "GraphicsManager.h"
#include "constants.h"

namespace StarBangBang
{
	namespace GRAPHICS
	{
		const static float CULL_OFFSET = 80.0f;
		static bool isFullscreen = false;
		static bool enableRescale = true;
		static AEVec2 cameraPos{ 0, 0 };
		//static AEVec2 screenScaleRatio;
		static AEVec2 screenScaleRatio = {  TARGET_WINDOW_WIDTH / RESOLUTION_X, TARGET_WINDOW_HEIGHT / RESOLUTION_Y };
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

	void GRAPHICS::SetCameraPosition(float x, float y)
	{
		cameraPos.x = x;
		cameraPos.y = y;
	}

	bool GRAPHICS::CheckOutOfBounds(const AEMtx33& transformMtx)
	{
		if (transformMtx.m[0][2] > AEGetWindowWidth() / 2 + CULL_OFFSET || transformMtx.m[1][2] > AEGetWindowHeight() / 2 + CULL_OFFSET
			|| transformMtx.m[0][2] < -AEGetWindowWidth() / 2 - CULL_OFFSET || transformMtx.m[1][2] < -AEGetWindowHeight() / 2 - CULL_OFFSET)
			return true;
		return false;
	}

	AEVec2 GRAPHICS::GetCameraPosition()
	{
		return cameraPos;
	}

	void GRAPHICS::ResetCamera()
	{
		SetZoom(DEFAULT_ZOOM);
		SetCameraPosition(0, 0);
	}

	AEMtx33 GRAPHICS::GetScaleMatrix()
	{
		AEMtx33 mtx;
		AEMtx33 zoomMtx;
		AEMtx33 screenScaleMtx;

		AEVec2 scale = GetScreenScale();

		AEMtx33Scale(&zoomMtx, zoom, zoom);
		AEMtx33Scale(&screenScaleMtx, scale.x, scale.y);
		AEMtx33Concat(&mtx, &zoomMtx, &screenScaleMtx);

		return mtx;
	}

	AEMtx33 GRAPHICS::GetCameraMatrix()
	{
		AEMtx33 mtx;
		AEMtx33 translateMtx;
		AEMtx33 scaleMtx;

		scaleMtx = GetScaleMatrix();

		AEMtx33Trans(&translateMtx, -cameraPos.x, -cameraPos.y);
		AEMtx33Concat(&mtx, &translateMtx, &scaleMtx);

		return mtx;
	}

	void GRAPHICS::ApplyCameraMatrix(AEMtx33* mtx)
	{
		AEMtx33 camMtx = GetCameraMatrix();
		AEMtx33Concat(mtx, &camMtx, mtx);
	}

	AEVec2 GRAPHICS::GetScreenScale()
	{
		if (isFullscreen)
			return screenScaleRatio;
		else
			return { 1, 1 };
	}

	float StarBangBang::GRAPHICS::GetZoom()
	{
		return zoom;
	}

	void GRAPHICS::ScaleFullscreen(AEMtx33& mtx)
	{
		if (enableRescale && isFullscreen)
		{
			AEMtx33ScaleApply(&mtx, &mtx, screenScaleRatio.x, screenScaleRatio.y);
			//AEMtx33ScaleApply(&mtx, &mtx, 1 / 2.4f, 1 / 1.8f);
		}
	}

	void GRAPHICS::InverseScaleFullscreen(AEMtx33& mtx)
	{
		if (enableRescale && isFullscreen)
		{
			AEMtx33ScaleApply(&mtx, &mtx, 1 / screenScaleRatio.x, 1 / screenScaleRatio.y);
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

		AEMtx33 cameraMtx = GetCameraMatrix();
		AEMtx33Concat(&transformMtx, &cameraMtx, &transformMtx);

		if (CheckOutOfBounds(transformMtx))
			return;

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		// No tint
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

		// Set texture
		AEGfxTextureSet(texture, 0, 0);

		AEGfxSetTransform(transformMtx.m);

		// Set Transparency
		AEGfxSetTransparency(1.0f);

		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}

	void GRAPHICS::SetBackgroundColor(Color c)
	{
		AEGfxSetBackgroundColor(c.R(), c.G(), c.B());
	}

	void StarBangBang::GRAPHICS::SetScreenScaleRatio(float x, float y)
	{
		screenScaleRatio.x = x;
		screenScaleRatio.y = y;
	}
}



