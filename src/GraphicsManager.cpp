/******************************************************************************/
/*!
\title		Captain Stealth
\file		GraphicsManager.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Graphics System.
			Responsible for loading, unloading 
			and drawing of Sprites (Meshes and Textures).

			Calculates the transformations required to properly
			translate, rotate and scale game objects, and
			render them onto the screen.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#include "GraphicsManager.h"
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
		static AEVec2 screenScaleRatio = {  TARGET_WINDOW_WIDTH / RESOLUTION_X, TARGET_WINDOW_HEIGHT / RESOLUTION_Y };
	}

	/*!*************************************************************************
	 * \brief
	 * Loads a texture from the specified file path.
	 * \param filePath
	 * Path to the texture file.
	 * \return
	 * Pointer to the texture that was loaded.
	***************************************************************************/
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

	/*!*************************************************************************
	 * \brief
	 * Creates a square mesh.
	 * \param width
	 * Width of the mesh
	 * \param height
	 * Height of the mesh
	 * \return
	 * Pointer to the mesh that was created.
	***************************************************************************/
	AEGfxVertexList* StarBangBang::GraphicsManager::CreateMesh(float width, float height)
	{
		AEGfxVertexList* mesh;
		AEGfxMeshStart();

		// This shape has 2 triangles
		AEGfxTriAdd(
			-width / 2, -height / 2, 0xFFFFFFFF, 0.0f, 1.0f,
			width / 2, -height / 2, 0xFFFFFFFF, 1.0f, 1.0f,
			-width / 2, height / 2, 0xFFFFFFFF, 0.0f, 0.0f);

		AEGfxTriAdd(
			width / 2, -height / 2, 0xFFFFFFFF, 1.0f, 1.0f,
			width / 2, height / 2, 0xFFFFFFFF, 1.0f, 0.0f,
			-width / 2, height / 2, 0xFFFFFFFF, 0.0f, 0.0f);

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

	/*!*************************************************************************
	 * \brief
	 * Gets the base mesh ("normalized").
	 * \return
	 * Pointer to the base mesh.
	***************************************************************************/
	AEGfxVertexList* StarBangBang::GraphicsManager::GetMesh()
	{
		if (normalizedMesh == nullptr)
		{
			normalizedMesh = CreateMesh(GRAPHICS::MESH_WIDTH, GRAPHICS::MESH_HEIGHT);
		}
		return normalizedMesh;
	}

	/*!*************************************************************************
	 * \brief
	 * Creates a sprite.
	 * Loads a new texture from the path, creates a new mesh from the input dimensions.
	 * \param filePath
	 * Path to the texture file.
	 * \param width
	 * Width of the mesh.
	 * \param height
	 * Height of the mesh
	 * \return
	 * The Sprite object that was created.
	***************************************************************************/
	StarBangBang::Sprite StarBangBang::GraphicsManager::CreateSprite(const char* filePath, float width, float height)
	{
		return Sprite(LoadTexture(filePath), CreateMesh(width, height));
	}

	/*!*************************************************************************
	 * \brief
	 * Creates a sprite.
	 * Loads a new texture from the path, uses the base mesh if it exists,
	 * creates it otherwise.
	 * \param filePath
	 * Path to the texture file.
	 * \return
	 * The Sprite object that was created.
	***************************************************************************/
	StarBangBang::Sprite StarBangBang::GraphicsManager::CreateSprite(const char* filePath)
	{
		return Sprite(LoadTexture(filePath), GetMesh());
	}

	/*!*************************************************************************
	 * \brief
	 * Creates a sprite.
	 * Loads a new texture from the path, creates a new mesh from the input dimensions.
	 * \param filePath
	 * Path to the texture file.
	 * \param width
	 * Width of the mesh.
	 * \param height
	 * Height of the mesh
	 * \return
	 * The Sprite object that was created.
	***************************************************************************/
	StarBangBang::Sprite StarBangBang::GraphicsManager::CreateSprite(std::string filePath, float width, float height)
	{
		return CreateSprite(filePath.c_str(), width, height);
	}

	/*!*************************************************************************
	 * \brief
	 * Creates a sprite.
	 * Loads a new texture from the path, uses the base mesh if it exists,
	 * creates it otherwise.
	 * \param filePath
	 * Path to the texture file.
	 * \return
	 * The Sprite object that was created.
	***************************************************************************/
	StarBangBang::Sprite StarBangBang::GraphicsManager::CreateSprite(std::string filePath)
	{
		return CreateSprite(filePath.c_str());
	}

	/*!*************************************************************************
	 * \brief
	 * Unloads all textures that were loaded.
	 * \return
	 * void
	***************************************************************************/
	void StarBangBang::GraphicsManager::UnloadTextures()
	{
		for (AEGfxTexture* texture : textureList)
		{
			AEGfxTextureUnload(texture);
			texture = nullptr;
		}
		textureList.clear();
	}

	/*!*************************************************************************
	 * \brief
	 * Frees all meshes that were created.
	 * \return
	 * void
	***************************************************************************/
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

	/*!*************************************************************************
	 * \brief
	 * Sets the camera zoom.
	 * \param scale
	 * Zoom factor.
	 * \return
	 * void
	***************************************************************************/
	void StarBangBang::GRAPHICS::SetZoom(float scale)
	{
		zoom = scale;
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the position of the camera.
	 * \param x
	 * X component.
	 * \param x
	 * Y component.
	 * \return
	 * void
	***************************************************************************/
	void GRAPHICS::SetCameraPosition(float x, float y)
	{
		cameraPos.x = x;
		cameraPos.y = y;
	}

	/*!*************************************************************************
	 * \brief
	 * Checks if the object is outside of the screen (window).
	 * \param transformMtx
	 * Read-only reference to the matrix of the object to check.
	 * \return
	 * True if outside of screen, false otherwise.
	***************************************************************************/
	bool GRAPHICS::CheckOutOfBounds(const AEMtx33& transformMtx)
	{
		if (transformMtx.m[0][2] > AEGetWindowWidth() / 2 + CULL_OFFSET || transformMtx.m[1][2] > AEGetWindowHeight() / 2 + CULL_OFFSET
			|| transformMtx.m[0][2] < -AEGetWindowWidth() / 2 - CULL_OFFSET || transformMtx.m[1][2] < -AEGetWindowHeight() / 2 - CULL_OFFSET)
			return true;
		return false;
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the position of the camera.
	 * \return
	 * Position of the camera.
	***************************************************************************/
	AEVec2 GRAPHICS::GetCameraPosition()
	{
		return cameraPos;
	}

	/*!*************************************************************************
	 * \brief
	 * Resets the position and zoom of the camera.
	 * \return
	 * void
	***************************************************************************/
	void GRAPHICS::ResetCamera()
	{
		SetZoom(DEFAULT_ZOOM);
		SetCameraPosition(0, 0);
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the scaling matrix of the camera.
	 * \return
	 * The concatenated zoom and screen scaling matrix.
	***************************************************************************/
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

	/*!*************************************************************************
	 * \brief
	 * Gets the camera matrix.
	 * \return
	 * The camera matrix.
	***************************************************************************/
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

	/*!*************************************************************************
	 * \brief
	 * Applies the camera matrix.
	 * \param mtx
	 * Matrix to apply the camera matrix on.
	***************************************************************************/
	void GRAPHICS::ApplyCameraMatrix(AEMtx33* mtx)
	{
		AEMtx33 camMtx = GetCameraMatrix();
		AEMtx33Concat(mtx, &camMtx, mtx);
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the ratio of the window's dimensions to the target resolution.
	 * (For full screen)
	 * \return
	 * Screen Scale ratio.
	***************************************************************************/
	AEVec2 GRAPHICS::GetScreenScale()
	{
		if (isFullscreen)
			return screenScaleRatio;
		else
			return { 1, 1 };
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the zoom factor of the camera.
	 * \return
	 * Zoom value of the camera.
	***************************************************************************/
	float StarBangBang::GRAPHICS::GetZoom()
	{
		return zoom;
	}

	/*!*************************************************************************
	 * \brief
	 * Scales the input matrix for full screen.
	 * \param mtx
	 * Matrix to scale.
	 * \return
	 * void
	***************************************************************************/
	void GRAPHICS::ScaleFullscreen(AEMtx33& mtx)
	{
		if (enableRescale && isFullscreen)
		{
			AEMtx33ScaleApply(&mtx, &mtx, screenScaleRatio.x, screenScaleRatio.y);
		}
	}

	/*!*************************************************************************
	 * \brief
	 * I don't understand my code anymore.
	 * Takes the reciprocal of the screen scale ratio and scales
	 * the input matrix by it.
	 * \param mtx
	 * Matrix to scale.
	 * \return
	 * void
	***************************************************************************/
	void GRAPHICS::InverseScaleFullscreen(AEMtx33& mtx)
	{
		if (enableRescale && isFullscreen)
		{
			AEMtx33ScaleApply(&mtx, &mtx, 1 / screenScaleRatio.x, 1 / screenScaleRatio.y);
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Toggles full screen mode.
	 * \return
	 * void
	***************************************************************************/
	void StarBangBang::GRAPHICS::ToggleFullscreen()
	{
		isFullscreen = !isFullscreen;
		AEToogleFullScreen(isFullscreen);
	}

	/*!*************************************************************************
	 * \brief
	 * Checks if the game is currently in full screen.
	 * \return
	 * True if full screen, false otherwise
	***************************************************************************/
	bool GRAPHICS::IsFullscreen()
	{
		return isFullscreen;
	}

	/*!*************************************************************************
	 * \brief
	 * Calculates the required transformations to convert from world space to screen space
	 * then draws the image.
	 * \param mesh
	 * Mesh to use for drawing.
	 * \param texture
	 * Texture to use for drawing.
	 * \param c
	 * Color to tint.
	 * \param pos
	 * Position to draw at (World Position).
	 * \param scale
	 * Scale of the image.
	 * \param rotation
	 * Rotation of the image.
	 * \param transparency
	 * Transparency of the image.
	 * \return
	 * void
	***************************************************************************/
	void StarBangBang::GRAPHICS::DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, Color color, AEVec2 pos, AEVec2 scale, float rotation, float transparency)
	{
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
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
		AEGfxSetTintColor(color.R(), color.G(), color.B(), color.A());

		// Set texture
		AEGfxTextureSet(texture, 0, 0);

		AEGfxSetTransform(transformMtx.m);

		// Set Transparency
		AEGfxSetTransparency(transparency);

		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

		AEGfxSetTransparency(1.0f);
	}

	/*!*************************************************************************
	 * \brief
	 * Draws an image as an overlay (Ignores camera).
	 * \param mesh
	 * Mesh to use for drawing.
	 * \param texture
	 * Texture to use for drawing.
	 * \param scale
	 * Scale of the image.
	 * \param pos
	 * Position to draw at.
	 * \param c
	 * Color to tint.
	 * \param rescale
	 * Whether to rescale the image in full screen mode.
	 * \param transparency
	 * Transparency of the image.
	 * \return
	 * void
	***************************************************************************/
	void GRAPHICS::DrawOverlay(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 scale, AEVec2 pos, Color c, bool rescale, float transparency)
	{
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		if (texture)
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxTextureSet(texture, 0, 0);
		}
		else
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEMtx33 s, t, trans;
		
		AEMtx33Scale(&s, scale.x, scale.y);
		AEMtx33Trans(&t, pos.x, pos.y);
		AEMtx33Concat(&trans, &t, &s);

		if (rescale)
		{
			AEVec2 screenScale = GetScreenScale();
			AEMtx33Scale(&s, screenScale.x, screenScale.y);
			AEMtx33Concat(&trans, &s, &trans);
		}
		
		AEGfxSetTransform(trans.m);
		AEGfxSetTintColor(c.R(), c.G(), c.B(), c.A());
		AEGfxSetTransparency(transparency);
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
		AEGfxSetTransparency(1.0f);
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the background color to clear with.
	 * \param c
	 * Color of the background.
	 * \return
	 * void
	***************************************************************************/
	void GRAPHICS::SetBackgroundColor(Color c)
	{
		AEGfxSetBackgroundColor(c.R(), c.G(), c.B());
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the Ratio of the window's dimensions to the screen's dimensions (resolution)
	 * \param x
	 * Width ratio
	 * \param y
	 * height ratio
	 * \return
	 * void
	***************************************************************************/
	void StarBangBang::GRAPHICS::SetScreenScaleRatio(float x, float y)
	{
		screenScaleRatio.x = x;
		screenScaleRatio.y = y;
	}
}



