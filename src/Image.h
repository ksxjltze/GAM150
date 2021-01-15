#pragma once
#include "AEEngine.h"

namespace TempTeam
{
	class Image
	{
	public:
		Image();
		Image(AEGfxVertexList* mesh, AEGfxTexture* texture, float alpha);
		
		void Init(const char* path, float width, float height, float alpha);
		void Draw(AEVec2 position);
		void Exit();
	private:
		AEGfxVertexList* mesh;
		AEGfxTexture* texture;
		float alpha;
	};
}