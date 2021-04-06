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
	public:
		float angle;
		float range;
		Color color;
		

		void Start();
		void BuildMesh();
		void Update();
		void Draw();
	
		VisionCone(GameObject* gameObject,float angle,float range, Color color);

		~VisionCone();

	};
}

