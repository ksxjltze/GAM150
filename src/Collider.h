#pragma once

#include "Component.h"
namespace StarBangBang
{
	enum class ShapeType {Box,Circle};
	class Collider : public Component
	{
		
		public:
			bool isTrigger = false;
			//collider is 
			bool isStatic = false;
		protected:
			AEVec2 offset = { 0,0 };
			GameObject* gameObject;
			Collider(GameObject* _gameObject,bool _isStatic)
			{
				isTrigger = false;
				isStatic = _isStatic;
				gameObject = _gameObject;
			}
			~Collider() {}
			
			
	};
	class CircleCollider : public Collider 
	{
		private : 
			ShapeType shape = ShapeType::Circle;
		public:
			float radius;
			
			AEVec2 center = {0,0};
			CircleCollider(GameObject* _go, AEVec2 _center, float _rad = 1.0f);
		
			~CircleCollider(){}

	};

	class BoxCollider : public Collider
	{
		private:
			ShapeType shape = ShapeType::Box;
		public:
			AEVec2 min;		
			AEVec2 max;		
			AEVec2 extend;	//half of width and height 
			AEVec2 center;
			
			 float GetHeight();
		
			 float GetWidth();

			 BoxCollider(GameObject* _go, AEVec2 _center, float width = 1.0f, float height = 1.0f);

			~BoxCollider() {}
		
	};
}
