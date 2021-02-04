#include "BasicMeshShape.h"
using namespace StarBangBang;
const unsigned int sides = 30;
AEGfxVertexList* unitboxMesh;
AEGfxVertexList* unitcircleMesh;
void StarBangBang::InitBasicMesh()
{
	//build unit box mesh
	AEGfxMeshStart();
	AEGfxVertexAdd(-0.5f,0.5f, 0xFF00FF00,0.0f,0.0f);
	AEGfxVertexAdd(0.5f, 0.5f, 0xFF00FF00, 0.0f, 0.0f);
	AEGfxVertexAdd(0.5f, -0.5f, 0xFF00FF00, 0.0f, 0.0f);
	AEGfxVertexAdd(-0.5f, -0.5f, 0xFF00FF00, 0.0f, 0.0f);
	AEGfxVertexAdd(-0.5f, 0.5f, 0xFF00FF00, 0.0f, 0.0f);

	unitboxMesh = AEGfxMeshEnd();

	//build unit circle mesh
	AEGfxMeshStart();
	float interval = 2.0f * PI / sides;
	//float x = 0, y = 0;
	for (unsigned int i = 0; i < sides; i++)
	{
		float radian = interval * i;
	
		float x = sin(radian);
		float y = cos(radian);
		
		AEGfxVertexAdd(x,y, 0xFF00FF00,0.0f,0.0f);
		

	}
	AEGfxVertexAdd(0.0f, 1.0f, 0xFF00FF00, 0.0f, 0.0f);
	unitcircleMesh = AEGfxMeshEnd();
	
}
void StarBangBang::DrawBox(AEVec2 size,AEVec2 pos)
{
	AEMtx33 scale = AEMtx33();
	AEMtx33 result = AEMtx33();
	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33Scale(&scale,size.x, size.y);
	AEMtx33TransApply(&result,&scale,pos.x,pos.y);
	AEGfxSetTransform(result.m);
	AEGfxMeshDraw(unitboxMesh, AEGfxMeshDrawMode::AE_GFX_MDM_LINES_STRIP);
}


void StarBangBang::DrawCircle(float radius, AEVec2 pos)
{
	AEMtx33 scale = AEMtx33();
	AEMtx33 result = AEMtx33();
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33Scale(&scale, radius, radius);

	AEMtx33TransApply(&result, &scale, pos.x, pos.y);
	AEGfxSetTransform(result.m);
	AEGfxMeshDraw(unitcircleMesh, AEGfxMeshDrawMode::AE_GFX_MDM_LINES_STRIP);
}

void StarBangBang::FreeUnitMeshes(void)
{
	AEGfxMeshFree(unitboxMesh);
	AEGfxMeshFree(unitcircleMesh);
}