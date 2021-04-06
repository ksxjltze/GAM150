#include "VisionCone.h"
#include "CollisionManager.h"
#include "GraphicsManager.h"
#include "Detector.h"

void StarBangBang::VisionCone::Start()
{
	detector = gameObject->GetComponent<Detector>();

	assert(detector);
	BuildMesh();
}

void StarBangBang::VisionCone::BuildMesh()
{
	AEGfxMeshStart();
	
	AEVec2 forward{0.0f,1.0f};
	float h_angle = angle * 0.5f * (PI/180) ;
	AEVec2 pt1{ 0,0 }, pt2{ 0,1 }, pt3{ 0,1 };

	size_t h_segment = (size_t)ceil((double)segments / 2.0);
	float segment = h_angle / h_segment;

	for (size_t i = 0; i < h_segment; ++i)
	{
		float a = segment* i;
	

		AEMtx33 rot;
		AEMtx33Rot(&rot, a);
		AEMtx33MultVec(&pt3, &rot, &forward);
		

		AEGfxTriAdd(pt1.x, pt1.y, 0xFFFFFFFF, 0.0f, 0.0f,
					pt2.x, pt2.y, 0xFFFFFFFF, 0.0f, 0.0f,
					pt3.x, pt3.y, 0xFFFFFFFF, 0.0f, 0.0f );

		pt2 = pt3;
	}

	pt2 = { 0,1 }, pt3 = { 0,1 };
	for (size_t i = 0; i < h_segment; ++i)
	{
		float a = -segment * i;


		AEMtx33 rot;
		AEMtx33Rot(&rot, a);
		AEMtx33MultVec(&pt3, &rot, &forward);


		AEGfxTriAdd(pt1.x, pt1.y, 0xFFFFFFFF, 0.0f, 0.0f,
			pt2.x, pt2.y, 0xFFFFFFFF, 0.0f, 0.0f,
			pt3.x, pt3.y, 0xFFFFFFFF, 0.0f, 0.0f);

		pt2 = pt3;
	}

	mesh = AEGfxMeshEnd();
}

void StarBangBang::VisionCone::Update()
{
	// Set Rotation
	AEMtx33 rot, scale;
	AEMtx33RotDeg(&rot, detector->GetRotation());

	AEMtx33Scale(&scale, range, range);

	//scale
	AEMtx33Concat(&trans, &scale, &rot);
	// Set Transform
	AEMtx33TransApply(&trans, &trans, gameObject->transform.position.x, gameObject->transform.position.y);

	AEMtx33 cameraMtx = GRAPHICS::GetCameraMatrix();
	AEMtx33Concat(&trans, &cameraMtx, &trans);
}

void StarBangBang::VisionCone::Draw()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTransform(trans.m);

	AEGfxSetTintColor(detector->GetColor().R(), detector->GetColor().G(), detector->GetColor().B(), detector->GetColor().A());

	// Set Transparency
	AEGfxSetTransparency(0.5f);

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransparency(1.0f);
}

StarBangBang::VisionCone::VisionCone(GameObject* gameObject , float angle, float range , size_t segments)
:	Component(gameObject), detector{ nullptr }, mesh{ nullptr }, trans{ AEMtx33() }, 
	segments{ segments }, angle{ angle }, range{ range }
{
}

StarBangBang::VisionCone::~VisionCone()
{
	if(mesh)
		AEGfxMeshFree(mesh);
}
