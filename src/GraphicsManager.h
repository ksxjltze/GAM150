#pragma once
#include "Sprite.h"
#include <AEEngine.h>
#include <vector>

namespace StarBangBang
{
	void DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 pos);
	void DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 pos, AEVec2 scale);
	class GraphicsManager
	{
	public:
		AEGfxTexture* LoadTexture(const char* filePath);
		AEGfxVertexList* CreateMesh(float width, float height);
		Sprite CreateSprite(const char* filePath, float width, float height);
		void UnloadTextures();
		void FreeMeshes();

	private:
		std::vector<AEGfxVertexList*> meshList;
		std::vector<AEGfxTexture*> textureList;
	};
}