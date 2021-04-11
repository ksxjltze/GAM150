/******************************************************************************/
/*!
\title		Captain Stealth
\file		GraphicsManager.h
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

#pragma once
#include "Sprite.h"
#include "Color.h"
#include <AEEngine.h>
#include <vector>
#include <string>
#include "constants.h"

namespace StarBangBang
{
	namespace GRAPHICS
	{
		static float zoom = DEFAULT_ZOOM;

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
		void DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, Color c, AEVec2 pos, AEVec2 scale, float rotation, float transparency);

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
		void DrawOverlay(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 scale, AEVec2 pos, Color c, bool rescale = true, float transparency = 1.0f);

		/*!*************************************************************************
		 * \brief 
		 * Sets the background color to clear with.
		 * \param c
		 * Color of the background.
		 * \return
		 * void
		***************************************************************************/
		void SetBackgroundColor(Color c);

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
		void SetScreenScaleRatio(float x, float y);

		/*!*************************************************************************
		 * \brief 
		 * Sets the camera zoom.
		 * \param scale
		 * Zoom factor.
		 * \return
		 * void
		***************************************************************************/
		void SetZoom(float scale);

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
		void SetCameraPosition(float x, float y);

		/*!*************************************************************************
		 * \brief 
		 * Checks if the object is outside of the screen (window).
		 * \param transformMtx
		 * Read-only reference to the matrix of the object to check.
		 * \return
		 * True if outside of screen, false otherwise.
		***************************************************************************/
		bool CheckOutOfBounds(const AEMtx33& transformMtx);

		/*!*************************************************************************
		 * \brief 
		 * Gets the position of the camera.
		 * \return
		 * Position of the camera.
		***************************************************************************/
		AEVec2 GetCameraPosition();

		/*!*************************************************************************
		 * \brief 
		 * Resets the position and zoom of the camera.
		 * \return
		 * void
		***************************************************************************/
		void ResetCamera();

		/*!*************************************************************************
		 * \brief 
		 * Gets the scaling matrix of the camera.
		 * \return
		 * The concatenated zoom and screen scaling matrix.
		***************************************************************************/
		AEMtx33 GetScaleMatrix();

		/*!*************************************************************************
		 * \brief 
		 * Gets the camera matrix.
		 * \return
		 * The camera matrix.
		***************************************************************************/
		AEMtx33 GetCameraMatrix();

		/*!*************************************************************************
		 * \brief 
		 * Applies the camera matrix.
		 * \param mtx
		 * Matrix to apply the camera matrix on.
		***************************************************************************/
		void ApplyCameraMatrix(AEMtx33* mtx);

		/*!*************************************************************************
		 * \brief 
		 * Gets the ratio of the window's dimensions to the target resolution.
		 * (For full screen)
		 * \return
		 * Screen Scale ratio.
		***************************************************************************/
		AEVec2 GetScreenScale();

		/*!*************************************************************************
		 * \brief 
		 * Gets the zoom factor of the camera.
		 * \return
		 * Zoom value of the camera.
		***************************************************************************/
		float GetZoom();

		/*!*************************************************************************
		 * \brief 
		 * Scales the input matrix for full screen.
		 * \param mtx
		 * Matrix to scale.
		 * \return
		 * void
		***************************************************************************/
		void ScaleFullscreen(AEMtx33& mtx);

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
		void InverseScaleFullscreen(AEMtx33& mtx);

		/*!*************************************************************************
		 * \brief 
		 * Toggles full screen mode.
		 * \return
		 * void
		***************************************************************************/
		void ToggleFullscreen();

		/*!*************************************************************************
		 * \brief 
		 * Checks if the game is currently in full screen.
		 * \return
		 * True if full screen, false otherwise
		***************************************************************************/
		bool IsFullscreen();

	}

	class GraphicsManager
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Loads a texture from the specified file path.
		 * \param filePath
		 * Path to the texture file.
		 * \return 
		 * Pointer to the texture that was loaded.
		***************************************************************************/
		AEGfxTexture* LoadTexture(const char* filePath);

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
		AEGfxVertexList* CreateMesh(float width, float height); //create new quad mesh

		/*!*************************************************************************
		 * \brief 
		 * Gets the base mesh ("normalized").
		 * \return
		 * Pointer to the base mesh.
		***************************************************************************/
		AEGfxVertexList* GetMesh(); //get base quad mesh

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
		Sprite CreateSprite(const char* filePath, float width, float height); //create and use new quad mesh

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
		Sprite CreateSprite(std::string filePath, float width, float height);

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
		Sprite CreateSprite(const char* filePath); //use base quad mesh

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
		Sprite CreateSprite(std::string filePath); //use base quad mesh

		/*!*************************************************************************
		 * \brief 
		 * Unloads all textures that were loaded.
		 * \return
		 * void
		***************************************************************************/
		void UnloadTextures();

		/*!*************************************************************************
		 * \brief 
		 * Frees all meshes that were created.
		 * \return
		 * void
		***************************************************************************/
		void FreeMeshes();

	private:
		AEGfxVertexList* normalizedMesh {nullptr};
		std::vector<AEGfxVertexList*> meshList;
		std::vector<AEGfxTexture*> textureList;
	};
}