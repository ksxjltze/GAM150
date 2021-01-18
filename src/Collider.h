#pragma once
#include "GameObject.h"
namespace StarBangBang
{
	enum ShapeType {Box,Circle};
	class Collider
	{
		
		public:
			ShapeType shape;
			bool isTrigger = false;
			GameObject *gameObject;
			/*virtual void OnEnter() = 0;
			virtual void OnStay() = 0;
			virtual void OnExit() = 0;*/
			

	};
	class CircleCollider : Collider 
	{
		public:
			float radius;
			AEVec2 center = {0,0};
			CircleCollider(GameObject* _go, AEVec2 _center, float _rad = 1.0f);
		
			~CircleCollider(){}

	};
	class BoxCollider : Collider
	{
		public:
			AEVec2 min;		
			AEVec2 max;		
			AEVec2 extend;	//half of width and height 
			AEVec2 center;
			BoxCollider(AEVec2 _min, AEVec2 _max, AEVec2 _center, float width = 1.0f, float height = 1.0f);
			
			~BoxCollider(){}
			inline float GetHeight();
		
			inline float GetWidth();
		
	};
}
