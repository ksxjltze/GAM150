#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
namespace StarBangBang
{

	
	void InitBasicMesh();

	void DrawBox(AEVec2 size, AEVec2 pos);

	void DrawCircle(float radius, AEVec2 pos);

	void FreeUnitMeshes(void);

}