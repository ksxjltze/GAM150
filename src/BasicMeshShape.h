/******************************************************************************/
/*!
\title		Captain Stealth
\file		BasicMeshShape.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the declaration for BasicMeshShape.cpp
			Utilis for basic mesh shape for rendering
			Also for line rendering

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/


#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Color.h"

namespace StarBangBang
{
	namespace BasicMeshShape
	{

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
		bool ApplyTransform(AEVec2 size, AEVec2 pos);
	}
	


	/*!*************************************************************************
	****
		\brief
			Builds and init basic meshes 
		\param none
	
		\return
			void
	****************************************************************************
	***/
	void InitBasicMesh();



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
	void DrawBoxWired(AEVec2 size, AEVec2 pos, Color color = White);


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
	void DrawBox(AEVec2 size, AEVec2 pos , Color color = White);


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
	void DrawCircle(float radius, AEVec2 pos, Color color = White);



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
	void DrawLine(float length, AEVec2 pos, float angle, Color color = White);


	/*!*************************************************************************
	****
		\brief
			Free all the pre-builted unit meshes
		\param none
	
		\return
			void
	****************************************************************************
	***/
	void FreeUnitMeshes(void);

}