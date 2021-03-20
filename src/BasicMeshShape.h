#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Color.h"

namespace StarBangBang
{
	namespace BasicMeshShape
	{
		bool ApplyTransform(AEVec2 size, AEVec2 pos);
	}
	
	void InitBasicMesh();


	void DrawBoxWired(AEVec2 size, AEVec2 pos, Color color = White);

	void DrawBox(AEVec2 size, AEVec2 pos , Color color = White);

	void DrawCircle(float radius, AEVec2 pos, Color color = White);

	void DrawLine(float length, AEVec2 pos, float angle, Color color = White);

	void FreeUnitMeshes(void);

}