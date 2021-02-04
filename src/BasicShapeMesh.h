#pragma once
#include "Extern/AlphaEngine_V3.08/include/AEEngine.h"
namespace StarBangBang
{
	class BasicShapeMesh
	{	
		public:
			AEGfxVertexList* unitboxMesh;
			AEGfxVertexList* unitcirceMesh;
			BasicShapeMesh();
			~BasicShapeMesh();

			void BuildMeshes()
			{
				//build box mesh
				AEGfxMeshStart();

				AEGfxVertexAdd(-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
				AEGfxVertexAdd(0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
				AEGfxVertexAdd(0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
				AEGfxVertexAdd(-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
				AEGfxVertexAdd(-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

				unitboxMesh = AEGfxMeshEnd();
			}
		private:

	};

	BasicShapeMesh::BasicShapeMesh()
	{
	}

	BasicShapeMesh::~BasicShapeMesh()
	{
	} 
	 

}





