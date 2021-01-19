#pragma once
#include "Rigidbody.h"
#include <typeinfo>
#include <vector>
namespace StarBangBang
{	

	class GameObject 
	{
		public:
			virtual void Init() {};
			virtual void Update() {};
			virtual void Draw() {};
			virtual void Exit() {};
			Transform transform;
			bool isActive = true;
			float width, height;
			
	
	};
}