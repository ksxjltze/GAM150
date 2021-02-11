#pragma once
#include "Sprite.h"
#include <AEEngine.h>
#include <vector>

namespace StarBangBang
{
	namespace Graphics
	{
		static float zoom = 1;
		void DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 pos, AEVec2 scale, float rotation);
		void SetZoom(float scale);
		float GetZoom();
	}

	class GraphicsManager
	{
	public:
		AEGfxTexture* LoadTexture(const char* filePath);

		AEGfxVertexList* CreateMesh(float width, float height); //create new quad mesh
		AEGfxVertexList* GetMesh(); //get base quad mesh

		Sprite CreateSprite(const char* filePath, float width, float height); //create and use new quad mesh
		Sprite CreateSprite(const char* filePath); //use base quad mesh

		void UnloadTextures();
		void FreeMeshes();

	private:
		AEGfxVertexList* normalizedMesh {nullptr};
		std::vector<AEGfxVertexList*> meshList;
		std::vector<AEGfxTexture*> textureList;
	};
}