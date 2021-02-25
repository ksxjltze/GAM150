#pragma once
<<<<<<< HEAD

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
			GameObject* gameObject = nullptr;

			Collider(GameObject* _gameObject,bool _isStatic): Component(gameObject)
			{
				isTrigger = false;
				isStatic = _isStatic;
				gameObject = _gameObject;
			}
	
			Collider() : Component(gameObject) { isTrigger = false, isStatic = false; }
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
=======
#include "GameObject.h"
#include "Component.h"
namespace StarBangBang
{
	enum class ShapeType {Box,Circle};
	class Collider : public Component
	{
		
		public:
			bool isTrigger = false;
		protected:
			GameObject *gameObject = nullptr;
			/*virtual void OnEnter() = 0;
			virtual void OnStay() = 0;
			virtual void OnExit() = 0;*/
			

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
>>>>>>> Yg
		private:
			ShapeType shape = ShapeType::Box;
		public:
			AEVec2 min;		
			AEVec2 max;		
			AEVec2 extend;	//half of width and height 
			AEVec2 center;
<<<<<<< HEAD
			;
			inline float GetHeight()
			{
				return extend.y * 2.0f;
			}
		
			inline float GetWidth()
			{
				return extend.x * 2.0f;
			}

			 BoxCollider(GameObject* _go, AEVec2 _center, float width = 1.0f, float height = 1.0f);

			~BoxCollider() {}
=======
			
			~BoxCollider(){}
			 float GetHeight();
		
			 float GetWidth();

			BoxCollider(GameObject* _go,AEVec2 _center, float width = 1.0f, float height = 1.0f);
>>>>>>> Yg
		
	};
}
