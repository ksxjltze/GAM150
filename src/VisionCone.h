/******************************************************************************/
/*!
\title		Captain Stealth
\file		VisionCone.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the declaration for VisionCone.cpp
			Contains a vision cone class that handles building
			rendering of the vision cone

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/


#pragma once
#include "ComponentCRTP.h"
#include "Color.h"



namespace StarBangBang 
{
	//forward declare
	class Detector;


	class VisionCone : public Component<VisionCone>
	{
	private:
		//the cone mesh
		AEGfxVertexList* mesh;
		//the detector class to get information on detection
		Detector* detector;
		//the final tranformation matrix of the object
		AEMtx33 trans;
		//number of segments to use to render the cone
		//how smooth the cone will look depends on this
		size_t segments;
	public:
		//the cone angle
		float angle;
		//the cone vision range
		float range;

		void Start();
		void BuildMesh();
		void Update();
		void Draw();
	
		VisionCone(GameObject* gameObject,float angle,float range , size_t segments);

		~VisionCone();

	};
}

