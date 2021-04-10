/******************************************************************************/
/*!
\title		Captain Stealth
\file		BasicMeshShape.cpp
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the definition for BasicMeshShape.h
			Utilis for basic mesh shape for rendering
			Also for line rendering

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "BasicMeshShape.h"
#include "GraphicsManager.h"

using namespace StarBangBang;
//number of points use for circle rendering
const unsigned int sides = 30;

//unit box mesh
static AEGfxVertexList* unitboxMesh;
//unit box wired mesh
static AEGfxVertexList* unitboxWiredMesh;
//unit circle mesh
static AEGfxVertexList* unitcircleMesh;
//unit line 
static AEGfxVertexList* lineMesh;
//static AEGfxVertexList* unitboxMesh;


/*!*************************************************************************
****
	\brief
		Builds and init basic meshes
	\param none

	\return
		void
****************************************************************************
***/
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


/*!*************************************************************************
****
	\brief
		Draws a wired box
	\param size
		The size of the box
	\param pos
		The position of the box
	\param color
		The color used to render the box
	\return
		void
****************************************************************************
***/
void StarBangBang::DrawBoxWired(AEVec2 size,AEVec2 pos , Color color)
{
	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	if (!BasicMeshShape::ApplyTransform(size, pos))
		return;

	AEGfxSetTintColor(color.R(), color.G(), color.B(), color.A());
	AEGfxMeshDraw(unitboxWiredMesh, AEGfxMeshDrawMode::AE_GFX_MDM_LINES_STRIP);
}


/*!*************************************************************************
****
	\brief
		Draws a box
	\param size
		The size of the box
	\param pos
		The position of the box
	\param color
		The color used to render the box
	\return
		void
****************************************************************************
***/
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

/*!*************************************************************************
****
	\brief
		Draws a circle
	\param radius
		The radius of the circle
	\param pos
		The position of the circle
	\param color
		The color used to render the circle
	\return
		void
****************************************************************************
***/
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


/*!*************************************************************************
****
	\brief
		Draws a line
	\param length
		The length of the line
	\param pos
		The position of the line
	\param angle
		The angle of the line
	\param color
		The color used to render the line
	\return
		void
****************************************************************************
***/
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


/*!*************************************************************************
****
	\brief
		Free all the pre-builted unit meshes
	\param none

	\return
		void
****************************************************************************
***/
void StarBangBang::FreeUnitMeshes(void)
{
	AEGfxMeshFree(unitboxMesh);
	AEGfxMeshFree(unitcircleMesh);
	AEGfxMeshFree(unitboxWiredMesh);
	AEGfxMeshFree(lineMesh);
}

/*!*************************************************************************
****
	\brief
		Applies the camera transformation to the meshes
	\param size
		The size of the object
	\param pos
		The position of the object
	\return
		Whether the object will be outside of the viewport
****************************************************************************
***/
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
