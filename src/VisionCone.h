#pragma once
#include "Physics.h"
#include "ComponentCRTP.h"
#include "Color.h"


namespace StarBangBang 
{
	class Detector;


	class VisionCone : public Component<VisionCone>
	{
	private:
		AEGfxVertexList* mesh;
		Detector* detector;
		AEMtx33 trans;
		size_t segments;
	public:
		float angle;
		float range;

		void Start();
		void BuildMesh();
		void Update();
		void Draw();
	
		VisionCone(GameObject* gameObject,float angle,float range , size_t segments);

		~VisionCone();

	};
}

