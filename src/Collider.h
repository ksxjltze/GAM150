#pragma once
#include "GameObject.h"
#include "ComponentCRTP.h"

namespace StarBangBang
{


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
			float radius;
			AEVec2 center = { 0,0 };
		public:
			inline float GetRadius() const
			{
				return radius;
			}
			inline AEVec2 GetCenter() const
			{
				return center;
			}
			CircleCollider( AEVec2 _center, float _rad = 1.0f);
			void SetCenter(float x, float y);

			void Translate(float x, float y);
	};

	//AABB only
	class BoxCollider : public Collider 
	{
		private:
			AEVec2 min;
			AEVec2 max;
			AEVec2 extend;	//half of width and height 
			AEVec2 center;
			//indexes to cells they occupy
			std::vector<int> cell_indexes;
		public:
			bool hasBool;
			inline AEVec2 GetExtend() const
			{
				return extend;
			}
			inline AEVec2 GetCenter() const
			{
				return center;
			}

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

			BoxCollider Union(const BoxCollider&);

			const std::vector<int>& GetCellIndexes() const;

			BoxCollider( AEVec2 _center,bool _isStatic = true ,float width = 1.0f, float height = 1.0f);
			BoxCollider(AEVec2 min, AEVec2 max , bool isStatic = true);
			BoxCollider(const BoxCollider& rhs) = default;
			BoxCollider& operator=(const BoxCollider& rhs) = default;


			//parition cell functions
			void SetCenter(float x, float y);
			void Translate(float x, float y);
			void ClearCellList();
			unsigned int GetCellListSize() const;
			void AddToCellList(int);
 
	};
}
