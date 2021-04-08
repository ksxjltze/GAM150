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