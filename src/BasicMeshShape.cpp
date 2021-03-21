#include "BasicMeshShape.h"
#include "GraphicsManager.h"

using namespace StarBangBang;
const unsigned int sides = 30;

static AEGfxVertexList* unitboxMesh;
static AEGfxVertexList* unitboxWiredMesh;
static AEGfxVertexList* unitcircleMesh;
static AEGfxVertexList* lineMesh;
//static AEGfxVertexList* unitboxMesh;

void StarBangBang::InitBasicMesh()
{
	//build unit box wired mesh
	AEGfxMeshStart();
	AEGfxVertexAdd(-0.5f,0.5f, 0xFFFFFFFF,0.0f,0.0f);
	AEGfxVertexAdd(0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	unitboxWiredMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(unitboxWiredMesh, "Failed to create wired box\n");

	//build unit box  mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, -0.5, 0xFFFFFFFF, 1.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);

	unitboxMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(unitboxWiredMesh, "Failed to create box mesh\n");

	//build unit circle mesh
	AEGfxMeshStart();
	float interval = 2.0f * PI / sides;
	for (unsigned int i = 0; i < sides; i++)
	{
		float radian = interval * i;
	
		float y = static_cast<float>(sin(radian));
		float x = static_cast<float>(cos(radian));
		
		AEGfxVertexAdd(x,y, 0xFFFFFFFF,0.0f,0.0f);
		

	}
	AEGfxVertexAdd(1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	unitcircleMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(unitcircleMesh, "Failed to create wired circle\n");

	//build line mesh
	AEGfxMeshStart();

	AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(0.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	lineMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(lineMesh, "Failed to create line mesh!!");
}
void StarBangBang::DrawBoxWired(AEVec2 size,AEVec2 pos , Color color)
{
	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	if (!BasicMeshShape::ApplyTransform(size, pos))
		return;

	AEGfxSetTintColor(color.R(), color.G(), color.B(), color.A());
	AEGfxMeshDraw(unitboxWiredMesh, AEGfxMeshDrawMode::AE_GFX_MDM_LINES_STRIP);
}

void StarBangBang::DrawBox(AEVec2 size, AEVec2 pos, Color color)
{
	AEMtx33 scale = AEMtx33();
	AEMtx33 result = AEMtx33();

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	if (!BasicMeshShape::ApplyTransform(size, pos))
		return;

	AEGfxSetTintColor(color.R(), color.G(), color.B(), color.A());

	AEGfxMeshDraw(unitboxMesh, AEGfxMeshDrawMode::AE_GFX_MDM_TRIANGLES);
}


void StarBangBang::DrawCircle(float radius, AEVec2 pos,Color color)
{
	AEMtx33 scale = AEMtx33();
	AEMtx33 result = AEMtx33();

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	if (!BasicMeshShape::ApplyTransform({ radius, radius }, pos))
		return;

	AEGfxSetTintColor(color.R(), color.G(), color.B(), color.A());
	AEGfxMeshDraw(unitcircleMesh, AEGfxMeshDrawMode::AE_GFX_MDM_LINES_STRIP);
}

void StarBangBang::DrawLine(float length, AEVec2 pos, float angle, Color color)
{
	AEMtx33 scale = AEMtx33();
	AEMtx33 rot = AEMtx33();
	AEMtx33 result = AEMtx33();

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEMtx33Scale(&scale, length, length);
	AEMtx33RotDeg(&rot, angle);
	AEMtx33Concat(&result, &scale, &rot);

	AEMtx33TransApply(&result, &result, pos.x, pos.y); 
	GRAPHICS::ApplyCameraMatrix(&result);

	if (result.m[0][2] > AEGetWindowWidth() || result.m[1][2] > AEGetWindowHeight()
		|| result.m[0][2] < -AEGetWindowWidth() || result.m[1][2] < -AEGetWindowHeight())
		return;

	AEGfxSetTransform(result.m);
	AEGfxSetTintColor(color.R(), color.G(), color.B(), color.A());

	AEGfxMeshDraw(lineMesh, AEGfxMeshDrawMode::AE_GFX_MDM_LINES_STRIP);
}

void StarBangBang::FreeUnitMeshes(void)
{
	AEGfxMeshFree(unitboxMesh);
	AEGfxMeshFree(unitcircleMesh);
	AEGfxMeshFree(unitboxWiredMesh);
	AEGfxMeshFree(lineMesh);
}

bool StarBangBang::BasicMeshShape::ApplyTransform(AEVec2 size, AEVec2 pos)
{
	AEMtx33 scale;
	AEMtx33 result;

	AEMtx33Scale(&scale, size.x, size.y);
	AEMtx33TransApply(&result, &scale, pos.x, pos.y);
	GRAPHICS::ApplyCameraMatrix(&result);

	if (GRAPHICS::CheckOutOfBounds(result))
		return false;

	AEGfxSetTransform(result.m);
	return true;
}
