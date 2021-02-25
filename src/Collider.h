#pragma once
#include "GameObject.h"
#include "ComponentCRTP.h"

namespace StarBangBang
{
	

	enum class ShapeType {Box,Circle};
	class Collider : public Component<Collider>
	{

	public:
		bool isTrigger = false;
		//collider does not move
		bool isStatic = false;
		AEVec2 offset = { 0,0 };

		Collider() :Component(gameObject) { isTrigger = false, isStatic = false, offset = AEVec2{ 0,0 }, gameObject = nullptr; };
	};
			

	class CircleCollider : public Collider 
	{
		private : 
			ShapeType shape = ShapeType::Circle;
		public:
			float radius;
			AEVec2 center = {0,0};
			CircleCollider( AEVec2 _center, float _rad = 1.0f);

	};

	//AABB only
	class BoxCollider : public Collider
	{
		private:
			ShapeType shape = ShapeType::Box;
			AEVec2 min;
			AEVec2 max;
		public:
			
			AEVec2 extend;	//half of width and height 
			AEVec2 center;

			inline AEVec2 Min() const 
			{
				if (isStatic)
					return min;
				else
					return AEVec2{ center.x - extend.x , center.y - extend.y };
				
			}
			inline AEVec2 Max() const
			{
				if (isStatic)
					return max;
				else
					return AEVec2{ center.x + extend.x , center.y + extend.y };
				
			}
			inline float GetHeight() const
			{
				return extend.y * 2.0f;
			}
		
			inline float GetWidth() const
			{
				return extend.x * 2.0f;
			}

			 BoxCollider( AEVec2 _center, float width = 1.0f, float height = 1.0f);
			 BoxCollider(const BoxCollider& b) = default;
	};
}
