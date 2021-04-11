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

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
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

		void DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, Color c, AEVec2 pos, AEVec2 scale, float rotation, float transparency);
		void DrawOverlay(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 scale, AEVec2 pos, Color c, bool rescale = true, float transparency = 1.0f);

		void SetBackgroundColor(Color c);
		void SetScreenScaleRatio(float x, float y);
		void SetZoom(float scale);
		void SetCameraPosition(float x, float y);

		bool CheckOutOfBounds(const AEMtx33& transformMtx);
		AEVec2 GetCameraPosition();
		void ResetCamera();

		AEMtx33 GetScaleMatrix();
		AEMtx33 GetCameraMatrix();
		void ApplyCameraMatrix(AEMtx33* mtx);

		AEVec2 GetScreenScale();
		float GetZoom();

		void ScaleFullscreen(AEMtx33& mtx);
		void InverseScaleFullscreen(AEMtx33& mtx);
		void ToggleFullscreen();
		bool IsFullscreen();

	}

	class GraphicsManager
	{
	public:
		AEGfxTexture* LoadTexture(const char* filePath);

		AEGfxVertexList* CreateMesh(float width, float height); //create new quad mesh
		AEGfxVertexList* GetMesh(); //get base quad mesh

		Sprite CreateSprite(const char* filePath, float width, float height); //create and use new quad mesh
		Sprite CreateSprite(std::string filePath, float width, float height);
		Sprite CreateSprite(const char* filePath); //use base quad mesh
		Sprite CreateSprite(std::string filePath); //use base quad mesh

		void UnloadTextures();
		void FreeMeshes();

	private:
		AEGfxVertexList* normalizedMesh {nullptr};
		std::vector<AEGfxVertexList*> meshList;
		std::vector<AEGfxTexture*> textureList;
	};
}