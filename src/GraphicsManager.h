#pragma once
#include "Sprite.h"
#include <AEEngine.h>
#include <vector>
#include <string>

namespace StarBangBang
{
	namespace GRAPHICS
	{
		static float zoom = 1;

		void DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 pos, AEVec2 scale, float rotation);
		void SetAspectRatio(float x, float y);
		void SetZoom(float scale);

		AEVec2 GetScreenScale();
		float GetZoom();

		void ScaleFullscreen(AEMtx33& mtx);
		void ToggleFullscreen();

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